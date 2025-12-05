using Stylet;

namespace ImgSizer.Wpf
{
    // 负责整体窗口 & 模式切换
    public class RootViewModel : Conductor<Screen>.Collection.OneActive
    {
        public SingleConvertViewModel SingleConvert { get; }

        public AdvancedOptionsViewModel AdvancedOptions { get; }

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
        }

        public void ShowSingle()
        {
            ActivateItem(SingleConvert);
        }
    }
}
