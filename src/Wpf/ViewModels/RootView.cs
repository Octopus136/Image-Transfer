using Stylet;
using System.Collections.ObjectModel;
using System.Windows;

namespace ImgSizer.Wpf
{
    // 负责整体窗口 & 模式切换
    public class RootViewModel : Conductor<Screen>.Collection.OneActive
    {
        public ObservableCollection<LanguageItem> Languages { get; } =
        new ObservableCollection<LanguageItem>
        {
            new LanguageItem { DisplayName = "简体中文", Code = "zh-CN" },
            new LanguageItem { DisplayName = "繁體中文", Code = "zh-TW" },
            new LanguageItem { DisplayName = "English", Code = "en-US" },
        };

        private LanguageItem _selectedLanguage;
        public LanguageItem SelectedLanguage
        {
            get => _selectedLanguage;
            set
            {
                SetAndNotify(ref _selectedLanguage, value);
                if (value != null)
                {
                    ((App)Application.Current).ChangeLanguage(value.Code);
                }
            }
        }
        public SingleConvertViewModel SingleConvert { get; }

        public AdvancedOptionsViewModel AdvancedOptions { get; }

        private int _progress;
        public int Progress
        {
            get => _progress;
            set => SetAndNotify(ref _progress, value);
        }

        public RootViewModel(
            SingleConvertViewModel singleConvert,
            AdvancedOptionsViewModel advancedOptions)
        {
            SingleConvert = singleConvert;
            AdvancedOptions = advancedOptions;

            // 加入可切换的两个页面
            Items.AddRange(new Screen[] { SingleConvert });

            // 默认显示单图
            ActiveItem = SingleConvert;
            BindProgress(SingleConvert);

            SelectedLanguage = Languages[0]; // 默认中文
        }

        private void BindProgress(Screen screen)
        {
            if (screen is IProgressSource progressSource)
            {
                progressSource.PropertyChanged += (s, e) =>
                {
                    if (e.PropertyName == nameof(IProgressSource.Progress))
                    {
                        Progress = progressSource.Progress;
                    }
                };
            }
        }

        public void ShowSingle()
        {
            ActivateItem(SingleConvert);
        }
    }
}
