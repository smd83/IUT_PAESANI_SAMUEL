using System.IO.Ports;
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
using ExtendedSerialPort_NS;
using System.Windows.Threading;



namespace IUT_Paesani_Samuel
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        ExtendedSerialPort serialPort1;
        string receivedText = "";
        Robot robot = new Robot();
        public MainWindow()
        {
            InitializeComponent();
            DispatcherTimer timerAffichage;
            serialPort1 = new ExtendedSerialPort("COM6", 115200, Parity.None, 8, StopBits.One);
            serialPort1.DataReceived += SerialPort1_DataReceived;
            serialPort1.Open();
            timerAffichage = new DispatcherTimer();
            timerAffichage.Interval = new TimeSpan(0, 0, 0, 0, 100);
            timerAffichage.Tick += TimerAffichage_Tick; 
            timerAffichage.Start();


        }

        private void TimerAffichage_Tick(object? sender, EventArgs e)
        {
            textBoxRéception.Text += robot.receivedText;
            robot.receivedText = "";
        }

        public void SerialPort1_DataReceived(object sender, DataReceivedArgs e)
        {
            robot.receivedText += Encoding.UTF8.GetString(e.Data, 0, e.Data.Length);
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
            ClearMessage();
        
        }
        private void buttonTest_Click(object sender, RoutedEventArgs e)
        {
            byte[] byteList = new byte[20]; 
            for(int i = 0; i < 20; i++)
            {
                byteList[i] = (byte)(2 * i);
            }
        }
        private void buttonEnvoyer_KeyUp(object sender, RoutedEventArgs e) { }
        private void buttonTest_KeyUp(object sender, RoutedEventArgs e) { }
        private void buttonClear_KeyUp(object sender, RoutedEventArgs e) { }


        private void textBoxRéception_KeyUp(object sender, KeyEventArgs e)
        { }  
       

        private void SendMessage()
        {
            serialPort1.WriteLine(textBoxEmission.Text);
            //textBoxRéception.Text += "Reçu: " + textBoxEmission.Text + "\n" + "\r";
            textBoxEmission.Text = "";
            
        }
        private void ClearMessage()
        {
            textBoxRéception.Text = " ";
            textBoxEmission.Text = " ";
        }

        private void textBoxEmission_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                SendMessage();
            }
            if (e.Key == Key.Delete)
            {
                ClearMessage();
            }

        }
    }
}



