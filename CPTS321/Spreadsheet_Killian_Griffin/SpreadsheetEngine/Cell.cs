// <copyright file="CellMediator.cs" company="Killian Griffin">
// Copyright (c) Killian Griffin. All rights reserved.
// </copyright>
namespace SpreadsheetEngine
{
    using System.ComponentModel;

    /// <summary>
    /// Unit of Spreadsheet class that contains data entered by user.
    /// </summary>
    public abstract class Cell : INotifyPropertyChanged
    {
        /// <summary>
        /// Field that contains the inputted text in the cell.
        /// </summary>
        protected string text;

        /// <summary>
        /// Field that contains the calculated value of the contents of the cell.
        /// </summary>
        protected string value;

        private int rowIndex;

        private int columnIndex;

        private uint bgColor = 0xFFFFFFFF;

        /// <summary>
        /// Initializes a new instance of the <see cref="Cell"/> class.
        /// </summary>
        /// <param name="rowIndex">
        /// Denotes the row position of the cell.
        /// </param>
        /// <param name="columnIndex">
        /// Denotes the column position of the cell.
        /// </param>
        public Cell(int rowIndex, int columnIndex)
        {
            this.rowIndex = rowIndex;
            this.columnIndex = columnIndex;
            this.text = string.Empty;
            this.value = string.Empty;
        }

        /// <summary>
        /// Event that triggers on <see cref="text"/> changing.
        /// </summary>
        public event PropertyChangedEventHandler PropertyChanged = (sender, e) => { };

        /// <summary>
        /// Gets <see cref="rowIndex"/> data.
        /// </summary>
        public int RowIndex
        {
            get { return this.rowIndex; }
        }

        /// <summary>
        /// Gets <see cref="columnIndex"/> data.
        /// </summary>
        public int ColumnIndex
        {
            get { return this.columnIndex; }
        }

        /// <summary>
        /// Gets or sets <see cref="text"/> while triggering <see cref="PropertyChanged"/>
        /// event on changing <see cref="text"/>.
        /// </summary>
        public string Text
        {
            get
            {
                return this.text;
            }

            set
            {
                if (value != this.text)
                {
                    this.text = value;
                    this.PropertyChanged(this, new PropertyChangedEventArgs("Text"));
                }
            }
        }

        /// <summary>
        /// Gets <see cref="value"/> data.
        /// </summary>
        public string Value
        {
            get { return this.value; }
        }

        /// <summary>
        /// Gets or sets <see cref="bgColor"/> while triggering <see cref="PropertyChanged"/>
        /// event on changing <see cref="bgColor"/>.
        /// </summary>
        public uint BGColor
        {
            get
            {
                return this.bgColor;
            }

            set
            {
                if (value != this.bgColor)
                {
                    this.bgColor = value;
                    this.PropertyChanged(this, new PropertyChangedEventArgs("BGColor"));
                }
            }
        }

        public void Clear()
        {
            this.Text = string.Empty;
            this.BGColor = 0xFFFFFFFF;
        }

        /// <summary>
        /// Event handler for changing value on its corresponding
        /// <see cref="ExpressionTree"/> changing.
        /// </summary>
        /// <param name="sender">
        /// Denotes <see cref="ExpressionTree"/> that was changed.
        /// </param>
        /// <param name="e">
        /// Denotes property change info.
        /// </param>
        protected void VariablePropertyChangedEventHandler(object sender, PropertyChangedEventArgs e)
        {
            ExpressionTree changed = sender as ExpressionTree;
            this.value = changed.Evaluate().ToString();
            this.PropertyChanged(this, new PropertyChangedEventArgs("Value property changed"));
        }

        /// <summary>
        /// Event handler for changing the values of a property based
        /// on an undo/redo command.
        /// </summary>
        /// <param name="sender">
        /// <see cref="UndoRedoCommand"/> representing the change to be made
        /// to the cell property.
        /// </param>
        /// <param name="e">
        /// Event arguments.
        /// </param>
        public void UndoRedoEventHandler(object sender, EventArgs e)
        {
            UndoRedoCommand undoRedo = sender as UndoRedoCommand;
            if(undoRedo is UndoRedoColor)
            {
                this.BGColor = ((UndoRedoColor)undoRedo).Color;
            } else if(undoRedo is UndoRedoText)
            {
                this.Text = ((UndoRedoText)undoRedo).Text;
            }
        }
    }
}