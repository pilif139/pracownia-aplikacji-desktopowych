using System;
using System.IO;
using System.Windows;
using System.Windows.Media.Imaging;

namespace styczen2024_desktopowa
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void txtNumer_LostFocus(object sender, RoutedEventArgs e)
        {
            string numer = txtNumer.Text.Trim();

            string sciezkaZdjecie = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "materialy",
                                                  numer + "-zdjecie.jpg");
            string sciezkaOdcisk = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "materialy",
                                                 numer + "-odcisk.jpg");

            imgZdjecie.Source = WczytajObraz(sciezkaZdjecie);
            imgOdcisk.Source = WczytajObraz(sciezkaOdcisk);
        }

        private BitmapImage WczytajObraz(string sciezka)
        {
            if (!File.Exists(sciezka))
            {
                Console.WriteLine($"Nie znaleziono pliku: {sciezka}");
                return null;
            }

            var bitmap = new BitmapImage();
            bitmap.BeginInit();
            bitmap.CacheOption = BitmapCacheOption.OnLoad;
            bitmap.UriSource = new Uri(sciezka, UriKind.Absolute);
            bitmap.EndInit();
            return bitmap;
        }

        private void btnOk_Click(object sender, RoutedEventArgs e)
        {
            string imie = txtImie.Text.Trim();
            string nazwisko = txtNazwisko.Text.Trim();

            if (string.IsNullOrEmpty(imie) || string.IsNullOrEmpty(nazwisko))
            {
                MessageBox.Show("Wprowadź dane");
                return;
            }

            string kolor = PobierzZaznaczonyKolor();
            MessageBox.Show($"{imie} {nazwisko} kolor oczu {kolor}");
        }

        private string PobierzZaznaczonyKolor()
        {
            if (rbNiebieskie.IsChecked == true) return rbNiebieskie.Content.ToString();
            if (rbZielone.IsChecked == true) return rbZielone.Content.ToString();
            if (rbPiwne.IsChecked == true) return rbPiwne.Content.ToString();
            return string.Empty;
        }
    }
}