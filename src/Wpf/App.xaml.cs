using System.Linq;
using System;
using System.Windows;

namespace ImgSizer.Wpf
{
    public class LanguageItem
    {
        public string DisplayName { get; set; } = "";
        public string Code { get; set; } = "";
    }
    public partial class App : Application
    {
        public void ChangeLanguage(string langCode)
        {
            string fileName = $"Localizations/{langCode.ToLower()}.xaml";

            var newDict = new ResourceDictionary
            {
                Source = new Uri(fileName, UriKind.Relative)
            };

            var mergedDicts = Resources.MergedDictionaries;
            var existingDicts = mergedDicts
                .Where(d => d.Source != null &&
                            d.Source.OriginalString.StartsWith("Localizations/", StringComparison.OrdinalIgnoreCase))
                .ToList();

            foreach (var dict in existingDicts)
                mergedDicts.Remove(dict);

            mergedDicts.Add(newDict);
        }
    }

}
