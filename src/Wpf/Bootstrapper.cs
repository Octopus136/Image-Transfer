using Stylet;
using StyletIoC;

namespace ImgSizer.Wpf
{
    public class Bootstrapper : Bootstrapper<RootViewModel>
    {
        protected override void ConfigureIoC(IStyletIoCBuilder builder)
        {
            base.ConfigureIoC(builder);

            builder.Bind<RootViewModel>().ToSelf().InSingletonScope();
            builder.Bind<SingleConvertViewModel>().ToSelf().InSingletonScope();
            builder.Bind<AdvancedOptionsViewModel>().ToSelf().InSingletonScope();
        }
    }
}
