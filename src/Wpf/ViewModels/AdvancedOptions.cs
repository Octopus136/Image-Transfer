using Stylet;

namespace ImgSizer.Wpf
{
    public class AdvancedOptionsViewModel : PropertyChangedBase
    {
        // 是否展开高级选项
        private bool _isExpanded;
        public bool IsExpanded
        {
            get => _isExpanded;
            set => SetAndNotify(ref _isExpanded, value);
        }

        // 自定义 JPEG 质量
        private bool _useCustomJpegQuality;
        public bool UseCustomJpegQuality
        {
            get => _useCustomJpegQuality;
            set => SetAndNotify(ref _useCustomJpegQuality, value);
        }

        private int _customJpegQuality = 95;
        public int CustomJpegQuality
        {
            get => _customJpegQuality;
            set => SetAndNotify(ref _customJpegQuality, value);
        }

        // 自定义 PNG 压缩级别
        private bool _useCustomPngCompression;
        public bool UseCustomPngCompression
        {
            get => _useCustomPngCompression;
            set => SetAndNotify(ref _useCustomPngCompression, value);
        }

        private int _customPngCompression = 1;
        public int CustomPngCompression
        {
            get => _customPngCompression;
            set => SetAndNotify(ref _customPngCompression, value);
        }

        // 以后如果你要根据扩展名决定 extensionParam 的含义，也可以在这里加 Helper 方法
        private bool _isAdvancedOptionsExpanded;
        public bool IsAdvancedOptionsExpanded
        {
            get => _isAdvancedOptionsExpanded;
            set => SetAndNotify(ref _isAdvancedOptionsExpanded, value);
        }

        // Stylet: Command="{s:Action ToggleAdvancedOptions}"
        public void ToggleAdvancedOptions()
        {
            IsAdvancedOptionsExpanded = !IsAdvancedOptionsExpanded;
        }
    }
}
