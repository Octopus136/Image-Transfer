using Stylet;

namespace ImgSizer.Wpf
{
    // 负责整体窗口 & 模式切换
    public class RootViewModel : Conductor<Screen>.Collection.OneActive
    {
        public SingleConvert SingleConvert { get; }

        public RootViewModel(
            SingleConvert singleConvert)
        {
            SingleConvert = singleConvert;

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
