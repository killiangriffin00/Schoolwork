// <copyright file="CellMediator.cs" company="Killian Griffin">
// Copyright (c) Killian Griffin. All rights reserved.
// </copyright>
namespace SpreadsheetEngine.Test
{
    using System;
    using System.Collections.Generic;    using System.IO;
    using System.Xml;
    using NUnit.Framework;

    /// <summary>
    /// Contains unit tests for <see cref="Spreadsheet"/> class.
    /// </summary>
    public class SpreasheetUnitTest
    {
        /// <summary>
        /// Tests <see cref="Spreadsheet.GetCell(int, int)"/> method by validating
        /// the <see cref="Cell.RowIndex"/> and <see cref="Cell.ColumnIndex"/> fields
        /// in a <see cref="Spreadsheet"/> class instantiated with row and column counts
        /// 10, 10.
        /// </summary>
        [Test]
        public void GetCellTest()
        {
            Spreadsheet testSpreadsheet = new Spreadsheet(10, 10);
            Assert.That(testSpreadsheet.GetCell(6, 8).RowIndex, Is.EqualTo(6));
            Assert.That(testSpreadsheet.GetCell(6, 8).ColumnIndex, Is.EqualTo(8));
        }

        /// <summary>
        /// Tests <see cref="Spreadsheet.GetCell(int, int)"/> method by validating
        /// the <see cref="Spreadsheet"/> class throws an <see cref="ArgumentOutOfRangeException"/>
        /// on attempting to access a <see cref="Cell"/> outside of the range of the
        /// <see cref="Spreadsheet"/> class.
        /// </summary>
        [Test]
        public void GetCellTestExceptional()
        {
            Spreadsheet testSpreadsheet = new Spreadsheet(10, 10);
            Assert.Throws<ArgumentOutOfRangeException>(() => testSpreadsheet.GetCell(14, 14));
        }

        /// <summary>
        /// Tests <see cref="Spreadsheet.SetCellText(int, int, string)"/> method by validating
        /// the <see cref="Cell.Text"/> and <see cref="Cell.Value"/> properties have been changed 
        /// to the given <see cref="string"/>.
        /// </summary>
        [Test]
        public void SetCellTextTestNormalString()
        {
            Spreadsheet testSpreadsheet = new Spreadsheet(10, 10);
            testSpreadsheet.SetCellText(2, 2, "Test");
            Assert.That(testSpreadsheet.GetCell(2, 2).Text, Is.EqualTo("Test"));
            Assert.That(testSpreadsheet.GetCell(2, 2).Value, Is.EqualTo("Test"));
        }

        /// <summary>
        /// Tests <see cref="Spreadsheet.SetCellText(int, int, string)"/> method edge case
        /// by validating the <see cref="Cell.Text"/> and <see cref="Cell.Value"/> properties
        /// have been changed to the given null string.
        /// </summary>
        [Test]
        public void SetCellTextTestEdgeEmptyString()
        {
            Spreadsheet testSpreadsheet = new Spreadsheet(10, 10);
            testSpreadsheet.SetCellText(1, 1, "");
            Assert.That(testSpreadsheet.GetCell(2, 2).Text, Is.EqualTo(""));
            Assert.That(testSpreadsheet.GetCell(2, 2).Value, Is.EqualTo(""));
        }

        /// <summary>
        /// Tests <see cref="Spreadsheet.SetCellText(int, int, string)"/> method edge case
        /// by validating the <see cref="Cell.Text"/> and <see cref="Cell.Value"/> properties
        /// have been changed to the literal coordinate string, as the coordinate string is invalid.
        /// </summary>
        [Test]
        public void SetCellTextTestEdgeInvalidEquals()
        {
            Spreadsheet testSpreadsheet = new Spreadsheet(10, 10);
            testSpreadsheet.SetCellText(2, 2, "=Z85");
            Assert.That(testSpreadsheet.GetCell(2, 2).Text, Is.EqualTo("=Z85"));
            Assert.That(testSpreadsheet.GetCell(2, 2).Value, Is.EqualTo("=Z85"));
        }

        /// <summary>
        /// Tests <see cref="Spreadsheet.SetCellText(int, int, string)"/> method exceptional
        /// case by validating the method throws a <see cref="ArgumentOutOfRangeException"/>
        /// with indexes that are out of range.
        /// </summary>
        [Test]
        public void SetCellTextTestExceptional()
        {
            Spreadsheet testSpreadsheet = new Spreadsheet(10, 10);
            Assert.Throws<ArgumentOutOfRangeException>(() => testSpreadsheet.SetCellText(14, 11, "Test"));
        }

        /// <summary>
        /// Tests <see cref="Spreadsheet.DoUndo()"/> and related Undo/Redo
        /// functionality by setting text in a cell and undoing the action.
        /// </summary>
        [Test]
        public void UndoRedoTestNormalUndoText()
        {
            Spreadsheet testSpreadsheet = new Spreadsheet(10, 10);
            List<Cell> testCells = new List<Cell>();
            testCells.Add(testSpreadsheet.GetCell(2, 2));
            testSpreadsheet.SetCellText(2, 2, "Undo this");
            testSpreadsheet.AddUndo(new UndoRedoText(testCells, "Test"));
            testSpreadsheet.DoUndo();
            Assert.That(testSpreadsheet.GetCell(2, 2).Text, Is.EqualTo("Test"));
        }

        /// <summary>
        /// Tests <see cref="Spreadsheet.DoRedo()"/> and related Undo/Redo
        /// functionality by setting a custom text redo action and executing
        /// it using <see cref="Spreadsheet.DoRedo"/>.
        /// </summary>
        [Test]
        public void UndoRedoTestNormalRedoText()
        {
            Spreadsheet testSpreadsheet = new Spreadsheet(10, 10);
            List<Cell> testCells = new List<Cell>();
            testCells.Add(testSpreadsheet.GetCell(2, 2));
            testSpreadsheet.AddRedo(new UndoRedoText(testCells, "Test"));
            testSpreadsheet.DoRedo();
            Assert.That(testSpreadsheet.GetCell(2, 2).Text, Is.EqualTo("Test"));
        }

        /// <summary>
        /// Tests <see cref="Spreadsheet.DoUndo()"/> and related Undo/Redo
        /// functionality by setting color in a cell and undoing the action.
        /// </summary>
        [Test]
        public void UndoRedoTestNormalUndoColor()
        {
            Spreadsheet testSpreadsheet = new Spreadsheet(10, 10);
            uint testColor = 0xFF000FFF;
            List<Cell> testCells = new List<Cell>();
            testCells.Add(testSpreadsheet.GetCell(2, 2));
            testSpreadsheet.AddUndo(new UndoRedoColor(testCells, testColor));
            testSpreadsheet.DoUndo();
            Assert.That(testSpreadsheet.GetCell(2, 2).BGColor, Is.EqualTo(testColor));
        }

        /// <summary>
        /// Tests <see cref="Spreadsheet.DoRedo()"/> and related Undo/Redo
        /// functionality by setting a custom color redo action and executing
        /// it using <see cref="Spreadsheet.DoRedo()"/>.
        /// </summary>
        [Test]
        public void UndoRedoTestNormalRedoColor()
        {
            Spreadsheet testSpreadsheet = new Spreadsheet(10, 10);
            List<Cell> testCells = new List<Cell>();
            uint testColor = 0xFF000FFF;
            testCells.Add(testSpreadsheet.GetCell(2, 2));
            testSpreadsheet.AddRedo(new UndoRedoColor(testCells, testColor));
            testSpreadsheet.DoRedo();
            Assert.That(testSpreadsheet.GetCell(2, 2).BGColor, Is.EqualTo(testColor));
        }

        /// <summary>
        /// Tests <see cref="Spreadsheet.DoUndo()"/> and related Undo/Redo
        /// functionality by setting a custom text undo action with multiple
        /// target cells and executing it using <see cref="Spreadsheet.DoUndo()"/>.
        /// </summary>
        public void UndoRedoTestEdgeMulticellTextUndo()
        {
            Spreadsheet testSpreadsheet = new Spreadsheet(10, 10);
            List<Cell> testCells = new List<Cell>();
            testCells.Add(testSpreadsheet.GetCell(2, 2));
            testCells.Add(testSpreadsheet.GetCell(2, 3));
            testCells.Add(testSpreadsheet.GetCell(3, 2));
            testCells.Add(testSpreadsheet.GetCell(3, 3));
            testSpreadsheet.AddUndo(new UndoRedoText(testCells, "Test"));
            testSpreadsheet.DoUndo();
            Assert.That(testSpreadsheet.GetCell(2, 2).Text, Is.EqualTo("Test"));
        }

        /// <summary>
        /// Tests <see cref="Spreadsheet.DoRedo()"/> and related Undo/Redo
        /// functionality by setting a custom text redo action with multiple
        /// target cells and executing it using <see cref="Spreadsheet.DoRedo"/>.
        /// </summary>
        [Test]
        public void UndoRedoTestEdgeMulticellTextRedo()
        {
            Spreadsheet testSpreadsheet = new Spreadsheet(10, 10);
            List<Cell> testCells = new List<Cell>();
            testCells.Add(testSpreadsheet.GetCell(2, 2));
            testCells.Add(testSpreadsheet.GetCell(2, 3));
            testCells.Add(testSpreadsheet.GetCell(3, 2));
            testCells.Add(testSpreadsheet.GetCell(3, 3));
            testSpreadsheet.AddRedo(new UndoRedoText(testCells, "Test"));
            testSpreadsheet.DoRedo();
            Assert.That(testSpreadsheet.GetCell(2, 2).Text, Is.EqualTo("Test"));
        }

        /// <summary>
        /// Tests <see cref="Spreadsheet.Save(System.IO.Stream)"/> by generating a spreadsheet,
        /// using the save method to save the <see cref="Spreadsheet"/> to an XML file, and
        /// validating the contents of the file.
        /// </summary>
        [Test]
        public void SaveSpreadsheetTestNormal()
        {
            Spreadsheet testSpreadsheet = new Spreadsheet(10, 10);
            FileStream writeFile = new FileStream(Directory.GetParent(Environment.CurrentDirectory).Parent.Parent.Parent.FullName + "/testFile.xml", FileMode.OpenOrCreate);
            testSpreadsheet.SetCellText(1, 1, "24");
            testSpreadsheet.SetCellText(2, 2, "=B2");
            testSpreadsheet.SetCellText(4, 3, "82");
            testSpreadsheet.Save(writeFile);
            writeFile.Close();
            FileStream readFile = new FileStream(Directory.GetParent(Environment.CurrentDirectory).Parent.Parent.Parent.FullName + "/testFile.xml", FileMode.OpenOrCreate);
            StreamReader reader = new StreamReader(readFile);
            Assert.That(reader.ReadLine(), Is.EqualTo("<?xml version=\"1.0\" encoding=\"utf-8\"?>"));
            Assert.That(reader.ReadLine(), Is.EqualTo("<spreadsheet>"));
            Assert.That(reader.ReadLine(), Is.EqualTo("  <cell name=\"B2\">"));
            Assert.That(reader.ReadLine(), Is.EqualTo("    <bgcolor>FFFFFFFF</bgcolor>"));
            Assert.That(reader.ReadLine(), Is.EqualTo("    <text>24</text>"));
            Assert.That(reader.ReadLine(), Is.EqualTo("  </cell>"));
            Assert.That(reader.ReadLine(), Is.EqualTo("  <cell name=\"C3\">"));
            Assert.That(reader.ReadLine(), Is.EqualTo("    <bgcolor>FFFFFFFF</bgcolor>"));
            Assert.That(reader.ReadLine(), Is.EqualTo("    <text>=B2</text>"));
            Assert.That(reader.ReadLine(), Is.EqualTo("  </cell>"));
            Assert.That(reader.ReadLine(), Is.EqualTo("  <cell name=\"D5\">"));
            Assert.That(reader.ReadLine(), Is.EqualTo("    <bgcolor>FFFFFFFF</bgcolor>"));
            Assert.That(reader.ReadLine(), Is.EqualTo("    <text>82</text>"));
            Assert.That(reader.ReadLine(), Is.EqualTo("  </cell>"));
            Assert.That(reader.ReadLine(), Is.EqualTo("</spreadsheet>"));
            reader.Close();
        }

        /// <summary>
        /// Tests <see cref="Spreadsheet.Save(System.IO.Stream)"/> by writing an XML file,
        /// using the load method to load the XML file to a <see cref="Spreadsheet"/>,
        /// and validating the contents of the spreadsheet.
        /// </summary>
        [Test]
        public void LoadSpreadsheetTestNormal()
        {
            Spreadsheet testSpreadsheet = new Spreadsheet(10, 10);
            FileStream writeFile = new FileStream(Directory.GetParent(Environment.CurrentDirectory).Parent.Parent.Parent.FullName + "/testFile.xml", FileMode.OpenOrCreate);
            StreamWriter writer = new StreamWriter(writeFile);
            writer.WriteLine("<spreadsheet>");
            writer.WriteLine("  <cell name=\"B2\">");
            writer.WriteLine("    <bgcolor>FFFFFFFF</bgcolor>");
            writer.WriteLine("    <text>24</text>");
            writer.WriteLine("  </cell>");
            writer.WriteLine("  <cell name=\"C3\">");
            writer.WriteLine("    <bgcolor>FF8000FF</bgcolor>");
            writer.WriteLine("    <text>=B2</text>");
            writer.WriteLine("  </cell>");
            writer.WriteLine("  <cell name=\"D5\">");
            writer.WriteLine("    <bgcolor>FF8000FF</bgcolor>");
            writer.WriteLine("    <text>82</text>");
            writer.WriteLine("  </cell>");
            writer.WriteLine("</spreadsheet>");
            writeFile.Close();
            FileStream readFile = new FileStream(Directory.GetParent(Environment.CurrentDirectory).Parent.Parent.Parent.FullName + "/testFile.xml", FileMode.OpenOrCreate);
            testSpreadsheet.Load(readFile);
            readFile.Close();
            Assert.That(testSpreadsheet.GetCell(1, 1).Text, Is.EqualTo("24"));
            Assert.That(testSpreadsheet.GetCell(2, 2).Text, Is.EqualTo("=B2"));
            Assert.That(testSpreadsheet.GetCell(4, 3).Text, Is.EqualTo("82"));
        }

        /// <summary>
        /// Tests <see cref="Spreadsheet.Save(System.IO.Stream)"/> by writing an XML file
        /// with dummy elements, using the load method to load the XML file to a 
        /// <see cref="Spreadsheet"/>, and validating the contents of the spreadsheet.
        /// </summary>
        [Test]
        public void LoadSpreadsheetTestEdge()
        {
            Spreadsheet testSpreadsheet = new Spreadsheet(10, 10);
            FileStream writeFile = new FileStream(Directory.GetParent(Environment.CurrentDirectory).Parent.Parent.Parent.FullName + "/testFile.xml", FileMode.OpenOrCreate);
            StreamWriter writer = new StreamWriter(writeFile);
            writer.WriteLine("<spreadsheet>");
            writer.WriteLine("  <cell name=\"B2\">");
            writer.WriteLine("    <bgcolor>FFFFFFFF</bgcolor>");
            writer.WriteLine("    <text>24</text>");
            writer.WriteLine("  </cell>");
            writer.WriteLine("  <cell name=\"C3\">");
            writer.WriteLine("    <bgcolor>FFFFFFFF</bgcolor>");
            writer.WriteLine("    <testelement>test</testelement>");
            writer.WriteLine("    <text>=B2</text>");
            writer.WriteLine("  </cell>");
            writer.WriteLine("  <test>test</test>");
            writer.WriteLine("  <cell name=\"D5\">");
            writer.WriteLine("    <bgcolor>FFFFFFFF</bgcolor>");
            writer.WriteLine("    <text>82</text>");
            writer.WriteLine("  </cell>");
            writer.WriteLine("</spreadsheet>");
            writeFile.Close();
            FileStream readFile = new FileStream(Directory.GetParent(Environment.CurrentDirectory).Parent.Parent.Parent.FullName + "/testFile.xml", FileMode.OpenOrCreate);
            testSpreadsheet.Load(readFile);
            readFile.Close();
            Assert.That(testSpreadsheet.GetCell(1, 1).Text, Is.EqualTo("24"));
            Assert.That(testSpreadsheet.GetCell(2, 2).Text, Is.EqualTo("=B2"));
            Assert.That(testSpreadsheet.GetCell(4, 3).Text, Is.EqualTo("82"));
        }
    }
}