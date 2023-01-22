// <copyright file="CellMediator.cs" company="Killian Griffin">
// Copyright (c) Killian Griffin. All rights reserved.
// </copyright>
namespace SpreadsheetEngine
{
    using System.ComponentModel;
    using System.Drawing;
    using System.Xml;

    /// <summary>
    /// Contains two-dimensional <see cref="List{T}"/> of <see cref="Cell"/> classes
    /// that represents the spreadsheet application data.
    /// </summary>
    public class Spreadsheet
    {
        private readonly int rowCount;

        private readonly int columnCount;

        private List<List<CellMediator>>? sheet;

        private List<CellMediator> modified;

        private Dictionary<Cell, ExpressionTree> expressionMap;

        private Stack<UndoRedoCommand> undoStack;

        private Stack<UndoRedoCommand> redoStack;

        /// <summary>
        /// Initializes a new instance of the <see cref="Spreadsheet"/> class.
        /// </summary>
        /// <param name="rowCount">
        /// Denotes the row number of the cell.
        /// </param>
        /// <param name="columnCount">
        /// Denotes the column number of the cell.
        /// </param>
        public Spreadsheet(int rowCount, int columnCount)
        {
            this.sheet = new List<List<CellMediator>>();
            this.expressionMap = new Dictionary<Cell, ExpressionTree>();
            this.undoStack = new Stack<UndoRedoCommand>();
            this.redoStack = new Stack<UndoRedoCommand>();
            this.modified = new List<CellMediator>();
            CellMediator tempCell;
            for (int i = 0; i < rowCount; i++)
            {
                this.sheet.Add(new List<CellMediator>());
                for (int j = 0; j < columnCount; j++)
                {
                    tempCell = new CellMediator(i, j);
                    tempCell.PropertyChanged += this.CellPropertyChangedHandler;
                    this.sheet[i].Add(tempCell);
                }
            }

            this.rowCount = rowCount;
            this.columnCount = columnCount;
        }

        /// <summary>
        /// <see cref="Spreadsheet"/> event that triggers on
        /// <see cref="CellPropertyChangedHandler(object, PropertyChangedEventArgs)"/>
        /// call.
        /// </summary>
        public event PropertyChangedEventHandler CellPropertyChanged = (sender, e) => { };

        /// <summary>
        /// Gets <see cref="rowCount"/> data.
        /// </summary>
        public int RowCount
        {
            get { return this.rowCount; }
        }

        /// <summary>
        /// Gets <see cref="columnCount"/> data.
        /// </summary>
        public int ColumnCount
        {
            get { return this.columnCount; }
        }

        /// <summary>
        /// Gives data of <see cref="Cell"/> located at given indexes.
        /// </summary>
        /// <param name="rowIndex">
        /// Denotes the row position of the <see cref="Cell"/>.
        /// </param>
        /// <param name="columnIndex">
        /// Denotes the column position of the <see cref="Cell"/>.
        /// </param>
        /// <returns>
        /// <see cref="Cell"/> object at given indexes in the stored list.
        /// </returns>
        public Cell GetCell(int rowIndex, int columnIndex)
        {
            return this.sheet[rowIndex][columnIndex];
        }

        /// <summary>
        /// Adds an <see cref="UndoRedoCommand"/> to the <see cref="Spreadsheet.undoStack"/>.
        /// </summary>
        /// <param name="undoCommand">
        /// Denotes the <see cref="UndoRedoCommand"/> to be added to the stack.
        /// </param>
        public void AddUndo(UndoRedoCommand undoCommand)
        {
            this.undoStack.Push(undoCommand);
        }

        /// <summary>
        /// Preforms the <see cref="UndoRedoCommand"/> at the top of the <see cref="Spreadsheet.undoStack"/>.
        /// </summary>
        public void DoUndo()
        {
            UndoRedoCommand undo = this.undoStack.Pop();
            UndoRedoCommand redo = undo.GetInverse();
            undo.DoUndoRedo();
            this.AddRedo(redo);
        }

        /// <summary>
        /// Adds an <see cref="UndoRedoCommand"/> to the <see cref="Spreadsheet.redoStack"/>.
        /// </summary>
        /// <param name="undoCommand">
        /// Denotes the <see cref="UndoRedoCommand"/> to be added to the stack.
        /// </param>
        public void AddRedo(UndoRedoCommand undoCommand)
        {
            this.redoStack.Push(undoCommand);
        }

        /// <summary>
        /// Preforms the <see cref="UndoRedoCommand"/> at the top of the <see cref="Spreadsheet.redoStack"/>.
        /// </summary>
        public void DoRedo()
        {
            UndoRedoCommand redo = this.redoStack.Pop();
            UndoRedoCommand undo = redo.GetInverse();
            redo.DoUndoRedo();
            this.AddUndo(undo);
        }

        /// <summary>
        /// Gets the number of items in the <see cref="Spreadsheet.undoStack"/>.
        /// </summary>
        /// <returns>
        /// <see cref="int"/> representing the number if items in the stack.
        /// </returns>
        public int GetUndoStackSize()
        {
            return this.undoStack.Count;
        }

        /// <summary>
        /// Gets the number of items in the <see cref="Spreadsheet.redoStack"/>.
        /// </summary>
        /// <returns>
        /// <see cref="int"/> representing the number if items in the stack.
        /// </returns>
        public int GetRedoStackSize()
        {
            return this.redoStack.Count;
        }

        /// <summary>
        /// Gets the <see cref="UndoRedoCommand.CommandDescription"/> of the command
        /// at the top of the <see cref="Spreadsheet.undoStack"/>.
        /// </summary>
        /// <returns>
        /// <see cref="string"/> representing the command at the top of the stack.
        /// </returns>
        public string GetUndoStackCommandDescription()
        {
            return this.undoStack.First().CommandDescription;
        }

        /// <summary>
        /// Gets the <see cref="UndoRedoCommand.CommandDescription"/> of the command
        /// at the top of the <see cref="Spreadsheet.redoStack"/>.
        /// </summary>
        /// <returns>
        /// <see cref="string"/> representing the command at the top of the stack.
        /// </returns>
        public string GetRedoStackCommandDescription()
        {
            return this.redoStack.First().CommandDescription;
        }

        /// <summary>
        /// Sets the <see cref="Cell.Text"/> property at an index in the
        /// <see cref="Spreadsheet"/> to a specified value.
        /// </summary>
        /// <param name="rowIndex">
        /// Denotes the <see cref="Cell.RowIndex"/> of the
        /// <see cref="Cell"/> to be updated.
        /// </param>
        /// <param name="columnIndex">
        /// Denotes the <see cref="Cell.ColumnIndex"/> of the
        /// <see cref="Cell"/> to be updated.
        /// </param>
        /// <param name="text">
        /// Denotes the text that the <see cref="Cell.Text"/>
        /// property will be updated to.
        /// </param>
        public void SetCellText(int rowIndex, int columnIndex, string text)
        {
            this.GetCell(rowIndex, columnIndex).Text = text;
        }

        /// <summary>
        /// Demonstrates <see cref="Spreadsheet"/> functionality for viewing on DataGridView
        /// </summary>
        public void Demo()
        {
            Random randomGenerate = new Random();
            for (int i = 0; i < 50; ++i)
            {
                this.SetCellText(randomGenerate.Next(this.RowCount), randomGenerate.Next(this.ColumnCount), "Demo Spreadsheet");
            }

            for (int i = 0; i < this.RowCount; ++i)
            {
                this.SetCellText(i, 1, "This is Cell B" + (i + 1).ToString());
            }

            string temp = "=B";
            for (int i = 0; i < this.RowCount; ++i)
            {
                temp = temp + (i+1).ToString();
                this.SetCellText(i, 0, temp);
                temp = "=B";
            }
        }

        /// <summary>
        /// Invokes the <see cref="Cell.Clear()"/> methods of each cell modified
        /// in the <see cref="Spreadsheet"/> to clear all cells in the spreadsheet.
        /// </summary>
        public void ClearCells()
        {
            foreach (CellMediator cell in this.modified)
            {
                cell.Clear();
            }
        }

        /// <summary>
        /// Puts the data from the <see cref="Spreadsheet"/> class into an XML
        /// stream that can be loaded later.
        /// </summary>
        /// <param name="saveFile">
        /// Denotes the stream the file is to be saved to.
        /// </param>
        public void Save(Stream saveFile)
        {
            XmlWriterSettings settings = new XmlWriterSettings();
            settings.Indent = true;
            XmlWriter writer = XmlWriter.Create(saveFile, settings);
            writer.WriteStartElement("spreadsheet");
            foreach (CellMediator cell in this.modified)
            {
                writer.WriteStartElement("cell");
                writer.WriteAttributeString("name", this.GetCellName(cell));
                writer.WriteStartElement("bgcolor");
                writer.WriteValue($"{cell.BGColor:X}");
                writer.WriteEndElement();
                writer.WriteStartElement("text");
                writer.WriteValue(cell.Text);
                writer.WriteEndElement();
                writer.WriteEndElement();
                cell.Clear();
            }

            writer.WriteEndElement();
            writer.Close();
            this.modified.Clear();
        }

        /// <summary>
        /// Loads the data from an XML stream into the <see cref="Spreadsheet"/>
        /// class.
        /// </summary>
        /// <param name="saveFile">
        /// Denotes the stream the data is to be loaded from.
        /// </param>
        public void Load(Stream loadFile)
        {
            XmlReader reader = XmlReader.Create(loadFile);
            Cell currentCell;
            this.ClearCells();
            while (reader.LocalName != "spreadsheet")
            {
                reader.Read();
            }

            while (!(reader.LocalName == "spreadsheet" && reader.NodeType == XmlNodeType.EndElement))
            {
                while (reader.LocalName != "cell")
                {
                    reader.Read();
                    if (reader.LocalName == "spreadsheet" && reader.NodeType == XmlNodeType.EndElement)
                    {
                        break;
                    }
                }

                if (reader.LocalName == "spreadsheet" && reader.NodeType == XmlNodeType.EndElement)
                {
                    break;
                }

                int[] rowColumn = new int[2];
                rowColumn = this.GetCellIndicies(reader.GetAttribute(0));
                currentCell = this.GetCell(rowColumn[0], rowColumn[1]);
                while (!(reader.LocalName == "cell" && reader.NodeType == XmlNodeType.EndElement))
                {
                    if (reader.LocalName == "text")
                    {
                        reader.Read();
                        currentCell.Text = reader.Value;
                        reader.Read();
                    }

                    if (reader.LocalName == "bgcolor")
                    {
                        reader.Read();
                        currentCell.BGColor = uint.Parse(reader.Value, System.Globalization.NumberStyles.HexNumber);
                        reader.Read();
                    }

                    reader.Read();
                }

                reader.Read();
            }

            this.undoStack.Clear();
            this.redoStack.Clear();
            reader.Close();
        }

        /// <summary>
        /// Takes a cell name and converts it to its row and column indicies.
        /// </summary>
        /// <param name="cellName">
        /// Denotes the name of the cell.
        /// </param>
        /// <returns>
        /// <see cref="int[]"/> of size 2 containing the row and column number.
        /// </returns>
        private int[] GetCellIndicies(string cellName)
        {
            int[] rowColumn = new int[2];
            rowColumn[0] = int.Parse(cellName.Substring(1)) - 1;
            rowColumn[1] = cellName[0] - 65;
            return rowColumn;
        }

        /// <summary>
        /// Takes a <see cref="Cell"/> and returns the cell name in the spreadsheet.
        /// </summary>
        /// <param name="cell">
        /// Denotes the cell that the name is needed from.
        /// </param>
        /// <returns>
        /// <see cref="string"/> representing the cell name.
        /// </returns>
        private string GetCellName(CellMediator cell)
        {
            string row = (cell.RowIndex + 1).ToString();
            string column = ((char)(cell.ColumnIndex + 65)).ToString();
            return column + row;
        }

        private void CellPropertyChangedHandler(object sender, PropertyChangedEventArgs e)
        {
            CellMediator propertyChangedCell = (CellMediator)sender;
            int rowNum = 0, colNum = 0;
            if (!this.modified.Contains(propertyChangedCell))
            {
                this.modified.Add(propertyChangedCell);
            }

            if (propertyChangedCell.Text.Length > 0)
            {
                if (propertyChangedCell.Text[0] != '=')
                {
                    propertyChangedCell.SetValue(propertyChangedCell.Text);
                }
                else
                {
                    this.expressionMap[propertyChangedCell] = new ExpressionTree(propertyChangedCell.Text.Substring(1));
                    ExpressionTree expression = this.expressionMap[propertyChangedCell];
                    List<string> expressionVariables = expression.GetVariableNames();
                    for (int i = 0; i < expressionVariables.Count; i++)
                    {
                        try
                        {
                            colNum = expressionVariables[i][0] - 65;
                            rowNum = int.Parse(expressionVariables[i].Substring(1)) - 1;
                        }
                        catch (FormatException)
                        {
                            propertyChangedCell.SetValue(propertyChangedCell.Text);
                            this.CellPropertyChanged(propertyChangedCell, e);
                            return;
                        }

                        if (colNum > this.sheet[0].Count || rowNum > this.sheet.Count)
                        {
                            propertyChangedCell.SetValue(propertyChangedCell.Text);
                            this.CellPropertyChanged(propertyChangedCell, e);
                            return;
                        }

                        try
                        {
                            if (this.sheet[rowNum][colNum].Value != string.Empty)
                            {
                                expression.SetVariable(expressionVariables[i], int.Parse(this.sheet[rowNum][colNum].Value));
                                this.sheet[colNum][rowNum].PropertyChanged += expression.CellVariablePropertyChangedEventHandler;
                            }
                            else
                            {
                                propertyChangedCell.SetValue(propertyChangedCell.Text);
                                this.CellPropertyChanged(propertyChangedCell, e);
                                return;
                            }
                        }
                        catch (FormatException)
                        {
                            propertyChangedCell.SetValue(propertyChangedCell.Text);
                            this.CellPropertyChanged(propertyChangedCell, e);
                            return;
                        }
                    }

                    try
                    {
                        propertyChangedCell.SetValue(ref expression);
                    }
                    catch (KeyNotFoundException)
                    {
                        propertyChangedCell.SetValue(propertyChangedCell.Text);
                    }
                }
            }
            else
            {
                propertyChangedCell.SetValue(propertyChangedCell.Text);
            }

            this.CellPropertyChanged(propertyChangedCell, e);
            return;
        }

        /// <summary>
        /// Allows instantiation of <see cref="Cell"/> abstract class.
        /// </summary>
        public class CellMediator : Cell
        {
            /// <summary>
            /// Initializes a new instance of the <see cref="CellMediator"/> class through <see cref="Cell"/> class.
            /// </summary>
            /// <param name="rowIndex">
            /// Denotes the row position of the cell.
            /// </param>
            /// <param name="columnIndex">
            /// Denotes the column position of the cell.
            /// </param>
            public CellMediator(int rowIndex, int columnIndex)
                : base(rowIndex, columnIndex)
            {
            }

            /// <summary>
            /// Sets the value field of the <see cref="Cell"/> parent class.
            /// </summary>
            /// <param name="value">
            /// <see cref="string"/> value to set the value field to.
            /// </param>
            public void SetValue(string value)
            {
                this.value = value;
            }

            /// <summary>
            /// Sets the value field of the <see cref="Cell"/> parent class using the
            /// output of an <see cref="ExpressionTree"/>. Also binds the <see cref="ExpressionTree"/>
            /// property change event to this nodes VariablePropertyChangedEventHandler.
            /// </summary>
            /// <param name="value">
            /// <see cref="ExpressionTree"/> value to set the value field to.
            /// </param>
            public void SetValue(ref ExpressionTree expression)
            {
                this.value = expression.Evaluate().ToString();
                expression.PropertyChanged += this.VariablePropertyChangedEventHandler;
            }
        }
    }
}
