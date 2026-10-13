using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace IUT_Paesani_Samuel
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        public MainWindow()
        {
            InitializeComponent();
        }

        private void textBoxEmission_TextChanged(object sender, TextChangedEventArgs e)
        {

        }
        static bool color = false;
        private void buttonEnvoyer_Click(object sender, RoutedEventArgs e) {
            color =!color;
            if (color == false)
            {
                buttonEnvoyer.Background = Brushes.Beige;
            }
            else
            {


                buttonEnvoyer.Background = Brushes.RoyalBlue;
            }

        }

        private void textBoxRéception_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                SendMessage();
            }
        }

        private void SendMessage()
        {
           string message = textBoxEmission.GetLineText()
        }
    }
}



