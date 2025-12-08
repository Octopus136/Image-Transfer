using System;
using System.ComponentModel;
using System.Windows;
using System.Windows.Media.Animation;

namespace ImgSizer.Wpf
{
    public partial class RootView
    {
        private double _advancedContentHeight = 0;
        private bool _isLoadedMeasured = false;

        public RootView()
        {
            InitializeComponent();

            Loaded += RootView_Loaded;
        }

        private void RootView_Loaded(object sender, RoutedEventArgs e)
        {
            if (DataContext is RootViewModel vm)
            {
                AdvancedContent.Loaded += (_, _) =>
                {
                    AdvancedContent.UpdateLayout();
                    _advancedContentHeight = AdvancedContent.ActualHeight;
                    _isLoadedMeasured = true;
                };

                vm.AdvancedOptions.PropertyChanged += AdvancedOptionsOnPropertyChanged;
            }
        }

        private void AdvancedOptionsOnPropertyChanged(object? sender, PropertyChangedEventArgs e)
        {
            if (e.PropertyName != nameof(AdvancedOptionsViewModel.IsAdvancedOptionsExpanded))
                return;

            if (DataContext is not RootViewModel vm)
                return;

            var expanded = vm.AdvancedOptions.IsAdvancedOptionsExpanded;

            if (!_isLoadedMeasured)
            {
                AdvancedPanel.Visibility = Visibility.Visible;
                AdvancedPanel.Height = double.NaN; // Auto
                AdvancedPanel.Measure(new Size(ActualWidth, double.PositiveInfinity));
                AdvancedPanel.Arrange(new Rect(0, 0, ActualWidth, AdvancedPanel.DesiredSize.Height));
                AdvancedPanel.UpdateLayout();
                _advancedContentHeight = AdvancedPanel.ActualHeight;
                AdvancedPanel.Height = 0;
                AdvancedPanel.Visibility = Visibility.Collapsed;
                _isLoadedMeasured = true;
            }

            if (expanded)
            {
                AdvancedPanel.Visibility = Visibility.Visible;
                var anim = new DoubleAnimation
                {
                    From = 0,
                    To = _advancedContentHeight,
                    Duration = TimeSpan.FromMilliseconds(180),
                    AccelerationRatio = 0.2,
                    DecelerationRatio = 0.8
                };
                AdvancedPanel.BeginAnimation(HeightProperty, anim);
            }
            else
            {
                var currentHeight = AdvancedPanel.ActualHeight;
                var anim = new DoubleAnimation
                {
                    From = currentHeight,
                    To = 0,
                    Duration = TimeSpan.FromMilliseconds(180),
                    AccelerationRatio = 0.2,
                    DecelerationRatio = 0.8
                };
                anim.Completed += (_, _) =>
                {
                    AdvancedPanel.Visibility = Visibility.Collapsed;
                };
                AdvancedPanel.BeginAnimation(HeightProperty, anim);
            }
        }
    }
}
