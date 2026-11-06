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
        static int i=0;

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
                SendMessage();
               
            

        }
        private void buttonClear_Click(object sender, RoutedEventArgs e)
        {
            textBoxRéception.Text = " ";
            textBoxEmission.Text = " ";
        
        }
        private void buttonTest_Click(object sender, RoutedEventArgs e)
        { }
        private void buttonEnvoyer_KeyUp(object sender, RoutedEventArgs e) { }
        private void buttonTest_KeyUp(object sender, RoutedEventArgs e) { }
        private void buttonClear_KeyUp(object sender, RoutedEventArgs e) { }


        private void textBoxRéception_KeyUp(object sender, KeyEventArgs e)
        { }  
       

        private void SendMessage()
        {
            string message = textBoxEmission.GetLineText(i);
            while (message != null)
            {
                if (message == null)
                {
                    return;
                }
                else
                {
                    textBoxRéception.Text = "Reçu: " + message + "\n" + "\r";
                }
                i++;
            }
        }

        
    }
}



