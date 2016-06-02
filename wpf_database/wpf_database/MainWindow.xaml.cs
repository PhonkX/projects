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
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Data.SqlClient;
using System.Data;

namespace wpf_database
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        DataTable publishDataTable = null;
        DataTable booksDataTable = null;
        // SqlDataAdapter publishDataAdapter = null;
        DataTable authorsDataTable = null;
        string conn = @"Data Source=PHONKXPC\SQLEXPRESS;Initial Catalog=Books;Integrated Security=True";

        public MainWindow()
        {
            InitializeComponent();
        }

        private void OnPublishSelect(object sender, RoutedEventArgs e)
        {
            publishDataTable = new DataTable();
            using (SqlConnection sc = new SqlConnection(conn))
            {
                SqlCommand comm = new SqlCommand(@"SELECT * FROM dbo.Издательства", sc);
                var publishDataAdapter = new SqlDataAdapter(comm);
                publishDataAdapter.Fill(publishDataTable);
            }

            PublishDataGrid.BeginInit();
            PublishDataGrid.DataContext = publishDataTable;
            PublishDataGrid.Items.Refresh();
            PublishDataGrid.EndInit();
        }

        private void PublishDataGrid_AutoGeneratingColumn(object sender, Microsoft.Windows.Controls.DataGridAutoGeneratingColumnEventArgs e)
        {
            if (e.Column.Header.ToString() == "КИ")
            {
                e.Column.Visibility = Visibility.Collapsed;
            }
        }

        private void UpdateDb(string command)
        {
            DataTable dt = PublishDataGrid.DataContext as DataTable;
            //publishDataTable = dataGridPublish.DataContext as DataTable;
            if (publishDataTable != null)
            {
                using (SqlConnection sc = new SqlConnection(conn))
                {
                    SqlCommand comm = new SqlCommand(@"SELECT * FROM dbo.Издательства", sc);
                    var dataAdapter = new SqlDataAdapter(comm);
                    SqlCommandBuilder commBuilder = new SqlCommandBuilder(dataAdapter);
                    try
                    {
                        // dt.AcceptChanges();
                        dataAdapter.Update(dt);
                    }
                    catch (DBConcurrencyException) { }
                }
            }
        }

        private void PublishDataGrid_RowEditEnding(object sender, Microsoft.Windows.Controls.DataGridRowEditEndingEventArgs e)
        {
            (e.Row.Item as DataRowView).EndEdit();
            UpdateDb(@"SELECT * FROM dbo.Издательства");
        }

        private void OnBooksSelect(object sender, RoutedEventArgs e)
        {
            UpdateBooksGrid();
        }

        public void UpdateBooksGrid()
        {
            booksDataTable = new DataTable();
            using (SqlConnection sc = new SqlConnection(conn))
            {
                SqlCommand comm = new SqlCommand(@"SELECT * FROM GetBooks", sc);
                var booksDataAdapter = new SqlDataAdapter(comm);
                booksDataAdapter.Fill(booksDataTable);
            }

            BooksDataGrid.BeginInit();
            BooksDataGrid.DataContext = booksDataTable;
            BooksDataGrid.Items.Refresh();
            BooksDataGrid.EndInit();
        }

        private void BooksDataGrid_AutoGeneratingColumn(object sender, Microsoft.Windows.Controls.DataGridAutoGeneratingColumnEventArgs e)
        {
            if (e.Column.Header.ToString() == "КК")
            {
                e.Column.Visibility = Visibility.Collapsed;
            }
        }

        private void AddButton_Click(object sender, RoutedEventArgs e)
        {
            DetailWindow detailWindow = new DetailWindow(this);
            detailWindow.Show();
            UpdateBooksGrid();
        }

        private void OnAuthorsSelect(object sender, RoutedEventArgs e)
        {
            authorsDataTable = new DataTable();
            using (SqlConnection sc = new SqlConnection(conn))
            {
                SqlCommand comm = new SqlCommand(@"SELECT * FROM dbo.Авторы", sc);
                var authorsDataAdapter = new SqlDataAdapter(comm);
                authorsDataAdapter.Fill(authorsDataTable);
            }

            AuthorsDataGrid.BeginInit();
            AuthorsDataGrid.DataContext = authorsDataTable;
            AuthorsDataGrid.Items.Refresh();
            AuthorsDataGrid.EndInit();
        }

        private void AuthorsDataGrid_AutoGeneratingColumn(object sender, Microsoft.Windows.Controls.DataGridAutoGeneratingColumnEventArgs e)
        {
            if (e.Column.Header.ToString() == "КА")
            {
                e.Column.Visibility = Visibility.Collapsed;
            }
        }

        private void AuthorsDataGrid_RowEditEnding(object sender, Microsoft.Windows.Controls.DataGridRowEditEndingEventArgs e)
        {
            (e.Row.Item as DataRowView).EndEdit();
            UpdateDb(@"SELECT * FROM dbo.Авторы");
        }

        private void PublishDataGrid_PreviewKeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Delete)
            {
                try
                {
                    var index = PublishDataGrid.SelectedIndex;
                    if (index != publishDataTable.Rows.Count)
                    {
                        publishDataTable.Rows[index].Delete();
                        UpdateDb(@"SELECT * FROM dbo.Издательства");
                    }
                }
                catch (Exception)
                {
                    MessageBox.Show("Запись не может быть удалена");
                }
            }
        }

        private void AuthorsDataGrid_PreviewKeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Delete)
            {
                var index = AuthorsDataGrid.SelectedIndex;
                if (index != authorsDataTable.Rows.Count)
                {
                    authorsDataTable.Rows[AuthorsDataGrid.SelectedIndex].Delete();
                    UpdateDb(@"SELECT * FROM dbo.Авторы");
                }
            }
        }

        private void EditButton_Click(object sender, RoutedEventArgs e)
        {
            if (BooksDataGrid.SelectedIndex != -1)
            {
                DetailWindow dw = new DetailWindow(this);
                dw.FillForm(booksDataTable.Rows[BooksDataGrid.SelectedIndex]);
                dw.BookKey = (int)booksDataTable.Rows[BooksDataGrid.SelectedIndex][0];
                dw.Show();
                UpdateBooksGrid();
            }
        }

        private void DeleteButton_Click(object sender, RoutedEventArgs e)
        {
            using (SqlConnection sc = new SqlConnection(conn))
            {
                if (BooksDataGrid.SelectedIndex != -1)
                {
                    sc.Open();
                    string delete = "DELETE FROM dbo.КнигиАвторы WHERE КК = @bkey";
                    var comm = new SqlCommand(delete, sc);
                    var bookKeyParam1 = new SqlParameter("@bkey", SqlDbType.Int);
                    bookKeyParam1.Value = (int)booksDataTable.Rows[BooksDataGrid.SelectedIndex][0];
                    comm.Parameters.Add(bookKeyParam1);
                    comm.ExecuteNonQuery();
                    delete = "DELETE FROM dbo.Книги WHERE КК = @bkey";
                    comm = new SqlCommand(delete, sc);
                    var bookKeyParam2 = new SqlParameter("@bkey", SqlDbType.Int);
                    bookKeyParam2.Value = bookKeyParam1.Value;
                    booksDataTable.Rows[BooksDataGrid.SelectedIndex].Delete();
                    comm.Parameters.Add(bookKeyParam2);
                    comm.ExecuteNonQuery();
                }
            }
            UpdateBooksGrid();
        }

        private void Window_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            if (SizeToContent != SizeToContent.Manual && Width != 700)
            {
                SizeToContent = SizeToContent.Manual;
                MinWidth = Width;
            }
        }
    }
}
