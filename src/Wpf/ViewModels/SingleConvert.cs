using Stylet;
using ImgSizer.Bridge;
using System;
using System.Threading.Tasks;
using BridgeSingleConvert = ImgSizer.Bridge.SingleConvert;
using BridgeConvertResult = ImgSizer.Bridge.ConvertResult;
using BridgeAdvancedOptions = ImgSizer.Bridge.AdvancedOptions;
using System.Text.RegularExpressions;
using System.Windows.Input;
using System.Windows;
using System.Globalization;
using System.IO;
using static ImgSizer.Wpf.Localization;
using System.Collections.Generic;
using static BridgeConvertResultExtensions;

namespace ImgSizer.Wpf
{
    public class SingleConvertViewModel : Screen, IProgressSource
    {
        public AdvancedOptionsViewModel AdvancedOptions { get; }
        public SingleConvertViewModel(AdvancedOptionsViewModel advancedOptions)
        {
            AdvancedOptions = advancedOptions;
        }

        private long _sourceBytes;
        public long SourceBytes
        {
            get => _sourceBytes;
            private set => SetAndNotify(ref _sourceBytes, value);
        }
        private void UpdateSourceFileSize()
        {
            try
            {
                if (!string.IsNullOrWhiteSpace(_inputPath) && File.Exists(_inputPath))
                {
                    SourceBytes = new FileInfo(_inputPath).Length;
                }
                else
                {
                    SourceBytes = 0;
                }
            }
            catch
            {
                SourceBytes = 0;
            }
        }

        private string _inputPath = "";
        public string InputPath
        {
            get => _inputPath;
            set
            {
                if (SetAndNotify(ref _inputPath, value))
                {
                    UpdateSourceFileSize();
                    NotifyOfPropertyChange(nameof(CanConvert));
                }
            }
        }

        private string _outputPath = "";
        public string OutputPath
        {
            get => _outputPath;
            set
            {
                if (SetAndNotify(ref _outputPath, value))
                {
                    NotifyOfPropertyChange(nameof(CanConvert));
                }
            }
        }

        private string _targetSize = "";
        public string TargetSize
        {
            get => _targetSize;
            set
            {
                if (SetAndNotify(ref _targetSize, value))
                {
                    ValidateTargetSize();
                    NotifyOfPropertyChange(nameof(CanConvert));
                }
            }
        }

        private string _unit = "MB";
        public string Unit
        {
            get => _unit;
            set
            {
                if (value == _unit)
                    return;

                var oldUnit = _unit;

                if (SetAndNotify(ref _unit, value))
                {
                    NotifyOfPropertyChange(nameof(CanConvert));
                    ConvertTargetSizeBetweenUnits(oldUnit, _unit);
                }
            }
        }

        private int _progress;
        public int Progress
        {
            get => _progress;
            set => SetAndNotify(ref _progress, value);
        }

        private bool _isBusy;
        public bool IsBusy
        {
            get => _isBusy;
            set
            {
                if (SetAndNotify(ref _isBusy, value))
                {
                    NotifyOfPropertyChange(nameof(CanConvert));
                }
            }
        }

        private static readonly Regex _regex = new(@"^(0\.[0-9]+|[1-9]\d*(\.\d+)?)$");

        private string _targetSizeError = "";
        public string TargetSizeError
        {
            get => _targetSizeError;
            private set
            {
                if (SetAndNotify(ref _targetSizeError, value))
                {
                    NotifyOfPropertyChange(nameof(IsTargetSizeValid));
                }
            }
        }

        public bool IsTargetSizeValid => string.IsNullOrEmpty(TargetSizeError);

        private void ValidateTargetSize()
        {
            if (string.IsNullOrWhiteSpace(_targetSize))
            {
                TargetSizeError = GetString("TargetSizeErrorRequired");
                return;
            }

            if (!_regex.IsMatch(_targetSize))
            {
                TargetSizeError = GetString("TargetSizeErrorInvalidNumber");
                return;
            }

            TargetSizeError = null;
        }

        private void ConvertTargetSizeBetweenUnits(string fromUnit, string toUnit)
        {
            if (!IsTargetSizeValid)
                return;

            if (string.IsNullOrWhiteSpace(TargetSize))
                return;

            if (!decimal.TryParse(TargetSize, NumberStyles.Float, CultureInfo.CurrentCulture, out var size))
                return;

            decimal result = size;

            if (fromUnit == "KB" && toUnit == "MB")
            {
                result = size / 1024m;
            }
            else if (fromUnit == "MB" && toUnit == "KB")
            {
                result = size * 1024m;
            }

            TargetSize = result.ToString("0.####", CultureInfo.CurrentCulture);
        }


        // 浏览输入文件
        public void BrowseInput()
        {
            var dialog = new Microsoft.Win32.OpenFileDialog
            {
                Filter = GetString("ImageFileFilter")
            };

            if (dialog.ShowDialog() == true)
            {
                InputPath = dialog.FileName;

                var dir = System.IO.Path.GetDirectoryName(InputPath);
                var name = System.IO.Path.GetFileNameWithoutExtension(InputPath);
                var ext = System.IO.Path.GetExtension(InputPath);
                OutputPath = System.IO.Path.Combine(dir ?? string.Empty, $"{name}_output{ext}");
            }
        }

        // 浏览输出文件
        public void BrowseOutput()
        {
            var dialog = new Microsoft.Win32.SaveFileDialog
            {
                Filter = GetString("ImageFileFilter"),
                FileName = OutputPath
            };

            if (dialog.ShowDialog() == true)
            {
                OutputPath = dialog.FileName;
            }
        }

        // 关于
        public void About()
        {
            HandyControl.Controls.MessageBox.Info(GetString("AboutMessage"), GetString("AboutTitle"));
        }

        // 开始转换
        public async void Convert()
        {
            if (IsBusy) return;

            if (string.IsNullOrWhiteSpace(InputPath) || string.IsNullOrWhiteSpace(OutputPath))
            {
                HandyControl.Controls.MessageBox.Error(GetString("InputOutputMissing"));
                return;
            }
            if (!double.TryParse(TargetSize, out var target) || target <= 0)
            {
                HandyControl.Controls.MessageBox.Error(GetString("InvalidTargetSize"));
                return;
            }

            long targetBytes = Unit == "KB"
                ? (long)(target * 1024)
                : (long)(target * 1024 * 1024);

            IsBusy = true;
            Progress = 0;

            try
            {
                var result = await Task.Run(() =>
                {
                    try
                    {
                        var advancedOptions = BuildAdvancedOptions();

                        return BridgeSingleConvert.Convert(
                            InputPath,
                            OutputPath,
                            targetBytes,
                            SourceBytes,
                            advancedOptions,
                            progress => System.Windows.Application.Current.Dispatcher.Invoke(() =>
                            {
                                Progress = progress;
                            }));
                    }
                    catch (Exception ex)
                    {
                        return BridgeConvertResult.ErrUnknown;
                    }
                });

                if (result == BridgeConvertResult.OK)
                {
                    HandyControl.Controls.MessageBox.Success(GetString("ConversionSuccess"));
                }
                else
                {
                    string messageFormat = GetString("ConversionFailedWithReasonFormat");
                    string reason = GetString(result.GetResourceKey());
                    string message = string.Format(messageFormat, reason);

                    HandyControl.Controls.MessageBox.Error(message);
                }
            }
            finally
            {
                IsBusy = false;
            }
        }

        public bool CanConvert => !IsBusy
                                  && !string.IsNullOrWhiteSpace(InputPath)
                                  && !string.IsNullOrWhiteSpace(OutputPath)
                                  && !string.IsNullOrWhiteSpace(TargetSize)
                                  && IsTargetSizeValid;

        private BridgeAdvancedOptions BuildAdvancedOptions()
        {
            var options = new BridgeAdvancedOptions();

            options.useExperimentalStrategy = false; // AdvancedOptions.UseExperimentalStrategy;
            options.useCUDA = false;                // AdvancedOptions.UseCUDA;

            // JPEG 质量
            int jpegQuality = AdvancedOptions.UseCustomJpegQuality
                ? AdvancedOptions.CustomJpegQuality
                : 95;

            // PNG 压缩
            int pngCompression = AdvancedOptions.UseCustomPngCompression
                ? AdvancedOptions.CustomPngCompression
                : 1;

            double tolerancePercent = AdvancedOptions.UseCustomTolerance
                ? AdvancedOptions.CustomTolerance
                : 1.0;

            jpegQuality = jpegQuality < 0 ? 0 : (jpegQuality > 100 ? 100 : jpegQuality);
            pngCompression = pngCompression < 0 ? 0 : (pngCompression > 9 ? 9 : pngCompression);
            tolerancePercent = tolerancePercent < 0 ? 0 : (tolerancePercent > 100 ? 100 : tolerancePercent);

            options.jpegQuality = jpegQuality;
            options.pngCompression = pngCompression;
            options.toleranceRatio = tolerancePercent / 100.0;

            return options;
        }

    }
}