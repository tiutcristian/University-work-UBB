using System;
using System.Configuration;
using System.Data;
using System.Data.SqlClient;
using System.Windows.Forms;

namespace Lab1GUI
{
    public partial class Form1: Form
    {
        SqlConnection sqlConnection;
        SqlDataAdapter parentTableAdapter;
        SqlDataAdapter childTableAdapter;
        DataSet dataSet;
        BindingSource bindingSourceTeams;
        BindingSource bindingSourceAthletes;

        SqlCommandBuilder commandBuilder;

        string parentTableName;
        string childTableName;
        string parentTableQuery;
        string childTableQuery;
        string tablesRelationName;
        string parentTablePrimaryKey;
        string childTableForeignKey;

        public Form1()
        {
            InitializeComponent();
            FillData();
            initUI();
        }

        void initUI() 
        {
            label1.Text = parentTableName;
            label2.Text = childTableName;
        }

        void FillData()
        {
            sqlConnection = new SqlConnection(getConnectionString());

            parentTableName = "ProjectTeam";
            childTableName = "StudentMember";
            parentTablePrimaryKey = "id";
            childTableForeignKey = "project_team_id";
            parentTableQuery = getSelectQuery(parentTableName);
            childTableQuery = getSelectQuery(childTableName);
            tablesRelationName = parentTableName + childTableName;

            parentTableAdapter = new SqlDataAdapter(parentTableQuery, sqlConnection);
            childTableAdapter = new SqlDataAdapter(childTableQuery, sqlConnection);

            dataSet = new DataSet();

            parentTableAdapter.Fill(dataSet, parentTableName);
            childTableAdapter.Fill(dataSet, childTableName);

            commandBuilder = new SqlCommandBuilder(childTableAdapter);

            dataSet.Relations.Add(tablesRelationName,
                dataSet.Tables[parentTableName].Columns[parentTablePrimaryKey],
                dataSet.Tables[childTableName].Columns[childTableForeignKey]);

            bindingSourceTeams = new BindingSource();
            bindingSourceTeams.DataSource = dataSet.Tables[parentTableName];
            bindingSourceAthletes = new BindingSource(bindingSourceTeams, tablesRelationName);

            dataGridView1.DataSource = bindingSourceTeams;
            dataGridView2.DataSource = bindingSourceAthletes;

            childTableAdapter.UpdateCommand = commandBuilder.GetUpdateCommand();
        }

        string getConnectionString()
        {
            return "Data Source=LENOVO-IPS3;Initial Catalog=PracticDBMS;Integrated Security=True;TrustServerCertificate=True";
        }

        string getSelectQuery(string tableName)
        {
            return "SELECT * FROM " + tableName;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                childTableAdapter.Update(dataSet, childTableName);
                dataSet.AcceptChanges();
                dataSet.Clear();
                parentTableAdapter.Fill(dataSet, parentTableName);
                childTableAdapter.Fill(dataSet, childTableName);
                MessageBox.Show("Update successful");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                sqlConnection.Close();
            }
        }
    }
}
