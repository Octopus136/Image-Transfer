namespace ImageTransfer.Wpf
{
    public static class Localization
    {
        public static string GetString(string key)
        {
            return System.Windows.Application.Current?.TryFindResource(key) as string ?? key;
        }
    }
}