// <copyright file="CellMediator.cs" company="Killian Griffin">
// Copyright (c) Killian Griffin. All rights reserved.
// </copyright>
namespace Spreadsheet_Killian_Griffin
{
    using System.ComponentModel;
    using SpreadsheetEngine;

    /// <summary>
    /// Represents a window that contains a <see cref="Spreadsheet"/>.
    /// </summary>
    public partial class Form1 : Form
    {
        private Spreadsheet mainSpreadsheet;

        /// <summary>
        /// Initializes a new instance of the <see cref="Form1"/> class.
        /// </summary>
        public Form1()
        {
            this.InitializeComponent();
            this.mainSpreadsheet = new Spreadsheet(50, 26);
            this.InitializeDataGrid();
            this.undoToolStripMenuItem.Enabled = false;
            this.redoToolStripMenuItem.Enabled = false;
        }

        /// <summary>
        /// Initializes cells in the main data grid.
        /// </summary>
        public void InitializeDataGrid()
        {
            this.mainDataGrid.Columns.Clear();
            for (char c = 'A'; c <= 'Z'; c++)
            {
                this.mainDataGrid.Columns.Add(c.ToString(), c.ToString());
            }

            this.mainDataGrid.Rows.Clear();
            for (int i = 0; i < 50; ++i)
            {
                this.mainDataGrid.Rows.Add();
                this.mainDataGrid.Rows[i].HeaderCell.Value = (i + 1).ToString();
            }

            this.mainSpreadsheet.CellPropertyChanged += this.DataGridPropertyHandler;
        }

        private void DataGridPropertyHandler(object sender, PropertyChangedEventArgs e)
        {
            Cell propertyChangedCell = (Cell)sender;
            this.undoToolStripMenuItem.ShowDropDown();
            this.mainDataGrid.Rows[propertyChangedCell.RowIndex].Cells[propertyChangedCell.ColumnIndex].Value = propertyChangedCell.Value;
            this.mainDataGrid.Rows[propertyChangedCell.RowIndex].Cells[propertyChangedCell.ColumnIndex].Style.BackColor = Color.FromArgb((int)propertyChangedCell.BGColor);
        }

        private void mainDataGrid_CellBeginEdit(object sender, DataGridViewCellCancelEventArgs e)
        {
            this.mainDataGrid.Rows[e.RowIndex].Cells[e.ColumnIndex].Value = this.mainSpreadsheet.GetCell(e.RowIndex, e.ColumnIndex).Text;
        }

        private void mainDataGrid_CellEndEdit(object sender, DataGridViewCellEventArgs e)
        {
            List<Cell> cellList = new List<Cell>();
            cellList.Add(this.mainSpreadsheet.GetCell(e.RowIndex, e.ColumnIndex));
            UndoRedoText undo = new UndoRedoText(cellList, cellList[0].Text);
            this.mainSpreadsheet.AddUndo(undo);
            this.undoToolStripMenuItem.Text = "Undo " + undo.CommandDescription;
            this.undoToolStripMenuItem.Enabled = true;

            this.mainSpreadsheet.SetCellText(e.RowIndex, e.ColumnIndex, this.mainDataGrid.Rows[e.RowIndex].Cells[e.ColumnIndex].Value.ToString());
            this.mainDataGrid.Rows[e.RowIndex].Cells[e.ColumnIndex].Value = this.mainSpreadsheet.GetCell(e.RowIndex, e.ColumnIndex).Value;
        }

        private void demoToolStripMenuItem_OnClick(object sender, EventArgs e)
        {
            this.mainSpreadsheet.Demo();
        }

        private void undoToolStripMenuItem_OnClick(object sender, EventArgs e)
        {
            this.mainSpreadsheet.DoUndo();
            this.redoToolStripMenuItem.Enabled = true;
            if (this.mainSpreadsheet.GetUndoStackSize() <= 0)
            {
                this.undoToolStripMenuItem.Enabled = false;
            }

            this.SetToolStripMenuItemText();
        }

        private void redoToolStripMenuItem_OnClick(object sender, EventArgs e)
        {
            this.mainSpreadsheet.DoRedo();
            this.undoToolStripMenuItem.Enabled = true;
            if (this.mainSpreadsheet.GetRedoStackSize() <= 0)
            {
                this.redoToolStripMenuItem.Enabled = false;
            }

            this.SetToolStripMenuItemText();
        }

        private void colorToolStripMenuItem_OnClick(object sender, EventArgs e)
        {
            Color cellColor = new Color();
            this.colorDialog1.ShowDialog();
            cellColor = this.colorDialog1.Color;
            List<Cell> cellList = new List<Cell>();
            foreach (DataGridViewCell cell in this.mainDataGrid.SelectedCells)
            {
                cellList.Add(this.mainSpreadsheet.GetCell(cell.RowIndex, cell.ColumnIndex));
            }

            UndoRedoColor undo = new UndoRedoColor(cellList, cellList[0].BGColor);
            this.mainSpreadsheet.AddUndo(undo);
            this.undoToolStripMenuItem.Text = "Undo " + undo.CommandDescription;
            this.undoToolStripMenuItem.Enabled = true;
            foreach (Cell cell in cellList)
            {
                cell.BGColor = (uint)cellColor.ToArgb();
            }
        }

        private void SetToolStripMenuItemText()
        {
            if (this.mainSpreadsheet.GetUndoStackSize() <= 0)
            {
                this.undoToolStripMenuItem.Text = "Undo";
            }
            else
            {
                this.undoToolStripMenuItem.Text = "Undo " + this.mainSpreadsheet.GetUndoStackCommandDescription();
            }

            if (this.mainSpreadsheet.GetRedoStackSize() <= 0)
            {
                this.redoToolStripMenuItem.Text = "Redo";
            }
            else
            {
                this.redoToolStripMenuItem.Text = "Redo " + this.mainSpreadsheet.GetRedoStackCommandDescription();
            }
        }

        private void saveToolStripMenuItem_OnClick(object sender, EventArgs e)
        {
            this.mainDataGrid.EndEdit();
            if (this.saveFileDialog.ShowDialog() == DialogResult.OK)
            {
                Stream file = this.saveFileDialog.OpenFile();
                this.mainSpreadsheet.Save(file);
                file.Close();
            }
        }

        private void loadToolStripMenuItem_OnClick(object sender, EventArgs e)
        {
            this.mainDataGrid.EndEdit();
            if (this.openFileDialog.ShowDialog() == DialogResult.OK)
            {
                Stream file = this.openFileDialog.OpenFile();
                this.mainSpreadsheet.Load(file);
                file.Close();
            }
        }
    }
}