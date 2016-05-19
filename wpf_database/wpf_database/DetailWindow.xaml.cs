using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Data.SqlClient;
using System.Data;

namespace wpf_database
{
    /// <summary>
    /// Interaction logic for DetailWindow.xaml
    /// </summary>
    public partial class DetailWindow : Window
    {
        string conn = @"Data Source=PHONKXPC\SQLEXPRESS;Initial Catalog=Books;Integrated Security=True";
        List<int> selectedAuthorsKeys = new List<int>();
        private bool isUpdate;
        private DataTable publishDataTable;
        private DataTable authorsDataTable;
        private SqlDataAdapter publishDataAdapter;
        private SqlDataAdapter authorsDataAdapter;
        private string bookName;
        private int bookPublishKey = -1;
        private int bookYear;
        private decimal bookPrice;
        public int BookKey { get; set; }

        public DetailWindow()
        {
            InitializeComponent();
        }

        private void CancelButton_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }

        public void FillForm(DataRow row)
        {
            NameTextBox.Text = row.ItemArray[1] as string;
            AuthorsTextBox.Text = row.ItemArray[3] as string;
            var publisher = row.ItemArray[2];// as string;
            PublishComboBox.SelectedItem = publisher;
            YearTextBox.Text = row.ItemArray[4].ToString();
            PriceTextBox.Text = row.ItemArray[5].ToString();
            isUpdate = true;
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            publishDataTable = new DataTable();
            authorsDataTable = new DataTable();
            using (SqlConnection sc = new SqlConnection(conn))
            {
                SqlCommand comm1 = new SqlCommand(@"SELECT * FROM dbo.Издательства", sc);
                publishDataAdapter = new SqlDataAdapter(comm1);
                publishDataAdapter.Fill(publishDataTable);
                SqlCommand comm2 = new SqlCommand(@"SELECT * FROM dbo.Авторы", sc);
                authorsDataAdapter = new SqlDataAdapter(comm2);
                authorsDataAdapter.Fill(authorsDataTable);
            }

            PublishComboBox.ItemsSource = publishDataTable.DefaultView;
            AuthorsComboBox.ItemsSource = authorsDataTable.DefaultView;
        }

        private void AuthorsComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            var item = (AuthorsComboBox.SelectedItem as DataRowView)["Фамилия"].ToString();
            if (AuthorsTextBox.Text == "")
            {
                AuthorsTextBox.Text += item;
                selectedAuthorsKeys.Add((int)AuthorsComboBox.SelectedValue);
            }
            else if(!AuthorsTextBox.Text.Contains(item))
            {
                AuthorsTextBox.Text += "," + item;
                selectedAuthorsKeys.Add((int)AuthorsComboBox.SelectedValue);
            }
        }

        private void ClearAuthorsButton_Click(object sender, RoutedEventArgs e)
        {
            AuthorsTextBox.Text = "";
            selectedAuthorsKeys.Clear();
        }

        private void UpdateDB()
        {
            try
            {
                using (SqlConnection sc = new SqlConnection(conn))
                {
                    sc.Open();
                    SqlParameter nameParam = new SqlParameter("@name", SqlDbType.NVarChar, -1);
                    nameParam.Value = bookName;
                    SqlParameter publishKeyParam = new SqlParameter("@pubkey", SqlDbType.Int);
                    publishKeyParam.Value = bookPublishKey;
                    SqlParameter yearParam = new SqlParameter("@year", SqlDbType.Int);
                    yearParam.Value = bookYear;
                    SqlParameter priceParam = new SqlParameter("@price", SqlDbType.Money);
                    priceParam.Value = bookPrice;
                    SqlParameter keyParam = new SqlParameter("@key", SqlDbType.Int);
                    keyParam.Value = BookKey;
                    string update = "UPDATE dbo.Книги SET "
                                    + "Название = @name, "
                                    + "КИ = @pubkey, "
                                    + "Год = @year,"
                                    + "Цена = @price "
                                    + "WHERE КК = @key";
                    var comm = new SqlCommand(update, sc);
                    comm.Parameters.Add(nameParam);
                    comm.Parameters.Add(publishKeyParam);
                    comm.Parameters.Add(yearParam);
                    comm.Parameters.Add(priceParam);
                    comm.Parameters.Add(keyParam);
                    comm.ExecuteNonQuery();
                    foreach (var authorKey in selectedAuthorsKeys)
                    {
                        SqlParameter bookKeyParam = new SqlParameter("@bkey", SqlDbType.Int);
                        bookKeyParam.Value = BookKey;
                        SqlParameter authorKeyParam = new SqlParameter("@akey", SqlDbType.Int);
                        authorKeyParam.Value = authorKey;
                        update = "UPDATE dbo.КнигиАвторы SET"
                                + "КА = @akey"
                                + "WHERE КК = @bkey";
                        comm = new SqlCommand(update, sc);
                        comm.Parameters.Add(bookKeyParam);
                        comm.Parameters.Add(authorKeyParam);
                        comm.ExecuteNonQuery();
                    }
                    Close();
                }
            }
            catch (Exception e)
            {
                MessageBox.Show(e.ToString(), e.Message);
            }
        }

        private void AddToDB()
        {//сначала вставляем новую книгу, получаем ключ, используя этот ключ, вставляем в "Книги-авторы"
           // string insertCommand = @"INSERT INTO dbo.Books (Название, КИ) ";
            try
            {
                using (SqlConnection sc = new SqlConnection(conn))
                {
                    sc.Open();
                    SqlParameter nameParam = new SqlParameter("@name", SqlDbType.NVarChar, -1);
                    nameParam.Value = bookName;
                    SqlParameter publishKeyParam = new SqlParameter("@pubkey", SqlDbType.Int);
                    publishKeyParam.Value = bookPublishKey;
                    SqlParameter yearParam = new SqlParameter("@year", SqlDbType.Int);
                    yearParam.Value = bookYear;
                    SqlParameter priceParam = new SqlParameter("@price", SqlDbType.Money);
                    priceParam.Value = bookPrice;
                    string insert = "INSERT INTO dbo.Книги (Название, КИ, Год, Цена) "
                                    + "VALUES (@name, @pubkey, @year, @price);" + 
                                    " SELECT CAST(SCOPE_IDENTITY() AS INT)";
                    var comm = new SqlCommand(insert, sc);
                    comm.Parameters.Add(nameParam);
                    comm.Parameters.Add(publishKeyParam);
                    comm.Parameters.Add(yearParam);
                    comm.Parameters.Add(priceParam);
                    int bookKey = (int) comm.ExecuteScalar();                   
                    foreach (var authorKey in selectedAuthorsKeys)
                    {
                        SqlParameter bookKeyParam = new SqlParameter("@bkey", SqlDbType.Int);
                        bookKeyParam.Value = bookKey;
                        SqlParameter authorKeyParam = new SqlParameter("@akey", SqlDbType.Int);
                        authorKeyParam.Value = authorKey;
                        insert = "Insert into dbo.КнигиАвторы (КК, КА) VALUES (@bkey, @akey)";
                        comm = new SqlCommand(insert, sc);
                        comm.Parameters.Add(bookKeyParam);
                        comm.Parameters.Add(authorKeyParam);
                        comm.ExecuteNonQuery();
                    }
                    Close();
                }
            }
            catch (Exception e)
            {
                MessageBox.Show(e.ToString(), e.Message);
            }
        }

        private bool СheckForm()
        {
            bookName = NameTextBox.Text.Trim();
            if (bookName == "")
            {
                MessageBox.Show("Некорректный формат поля 'Название'");
                return false;
            }
            //  bookPublishName = PublishComboBox.Selected.Trim();
            if (PublishComboBox.SelectedIndex < 0)
            {
                MessageBox.Show("Неверный формат поля 'Издательство'");
                return false;
            }
            else
            {
                bookPublishKey = (int) PublishComboBox.SelectedValue;
            }
            /*if (AuthorsTextBox.Text.Trim() == "")
                MessageBox.Show("Неверный формат поля 'Авторы'");*/
            if (!int.TryParse(YearTextBox.Text, out bookYear))
            {
                MessageBox.Show("Неверный формат поля 'Год'. Введите число.");
                return false;
            }
            if (!decimal.TryParse(PriceTextBox.Text, out bookPrice))
            {
                MessageBox.Show("Неверный формат поля 'Цена'. Введите число.");
                return false;
            }
            return true;
        }

        private void SaveButton_Click(object sender, RoutedEventArgs e)
        {
            if (СheckForm())
            {
                if (isUpdate)
                {
                    UpdateDB();
                }
                else
                {
                    AddToDB();
                }
            }
        }
    }
}
