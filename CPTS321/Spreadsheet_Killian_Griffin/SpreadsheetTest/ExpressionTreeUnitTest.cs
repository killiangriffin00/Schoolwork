// <copyright file="CellMediator.cs" company="Killian Griffin">
// Copyright (c) Killian Griffin. All rights reserved.
// </copyright>
namespace SpreadsheetEngine.Test
{
    using System;
    using System.Collections.Generic;
    using NUnit.Framework;

    /// <summary>
    /// Test suite testing methods of <see cref="ExpressionTree"/> class.
    /// </summary>
    public class ExpressionTreeUnitTest
    {
        /// <summary>
        /// Tests <see cref="ExpressionTree"/> method <see cref="ExpressionTree.SetVariable(string, double)"/>
        /// by evaluating an <see cref="ExpressionTree"/> with one varible.
        /// </summary>
        [Test]
        public void ExpressionTreeTestSetVariableNormal()
        {
            ExpressionTree tree = new ExpressionTree("4-AE");
            tree.SetVariable("AE", 2);
            Assert.That(tree.Evaluate(), Is.EqualTo(2));
        }

        /// <summary>
        /// Tests <see cref="ExpressionTree"/> method <see cref="ExpressionTree.SetVariable(string, double)"/>
        /// by evaluating an <see cref="ExpressionTree"/> with one varible
        /// and checking for lack of case sensitivity.
        /// </summary>
        [Test]
        public void ExpressionTreeTestSetVariableEdge()
        {
            ExpressionTree tree = new ExpressionTree("4-ae");
            tree.SetVariable("AE", 2);
            Assert.That(tree.Evaluate(), Is.EqualTo(2));
        }

        /// <summary>
        /// Tests <see cref="ExpressionTree"/> method <see cref="ExpressionTree.Evaluate()"/>
        /// by creating an <see cref="ExpressionTree"/> with a string
        /// of additions and verifying proper output.
        /// </summary>
        [Test]
        public void ExpressionTreeTestEvaluateNormalAdd()
        {
            ExpressionTree tree = new ExpressionTree("1+2+3");
            Assert.That(tree.Evaluate(), Is.EqualTo(6));
        }

        /// <summary>
        /// Tests <see cref="ExpressionTree"/> method <see cref="ExpressionTree.Evaluate()"/>
        /// by creating an <see cref="ExpressionTree"/> with a string
        /// of subtractions and verifying proper output.
        /// </summary>
        [Test]
        public void ExpressionTreeTestEvaluateNormalSubtract()
        {
            ExpressionTree tree = new ExpressionTree("6-5");
            Assert.That(tree.Evaluate(), Is.EqualTo(1));
        }

        /// <summary>
        /// Tests <see cref="ExpressionTree"/> method <see cref="ExpressionTree.Evaluate()"/>
        /// by creating an <see cref="ExpressionTree"/> with a string
        /// of multiplications and verifying proper output.
        /// </summary>
        [Test]
        public void ExpressionTreeTestEvaluateNormalMultiply()
        {
            ExpressionTree tree = new ExpressionTree("3*2*4");
            Assert.That(tree.Evaluate(), Is.EqualTo(24));
        }

        /// <summary>
        /// Tests <see cref="ExpressionTree"/> method <see cref="ExpressionTree.Evaluate()"/>
        /// by creating an <see cref="ExpressionTree"/> with a string
        /// of divisions and verifying proper output.
        /// </summary>
        [Test]
        public void ExpressionTreeTestEvaluateNormalDivide()
        {
            ExpressionTree tree = new ExpressionTree("2/4");
            Assert.That(tree.Evaluate(), Is.EqualTo(.5));
        }

        /// <summary>
        /// Tests <see cref="ExpressionTree"/> method <see cref="ExpressionTree.Evaluate()"/>
        /// by creating an <see cref="ExpressionTree"/> with a string
        /// containing variables and verifying proper output.
        /// </summary>
        [Test]
        public void ExpressionTreeTestEvaluateEdge()
        {
            ExpressionTree tree = new ExpressionTree("1+2+ae+4");
            tree.SetVariable("ae", 2);
            Assert.That(tree.Evaluate(), Is.EqualTo(9));
        }

        /// <summary>
        /// Tests <see cref="ExpressionTree"/> method <see cref="ExpressionTree.GetVariableNames()"/>
        /// by instantiating an <see cref="ExpressionTree"/> class, adding variables to it, and
        /// validating the output.
        /// </summary>
        [Test]
        public void ExpressionTreeGetVariableNamesNormal()
        {
            ExpressionTree tree = new ExpressionTree("1+A1+A2");
            List<string> variableNames = tree.GetVariableNames();
            Assert.That(variableNames.Contains("A1"), Is.True);
            Assert.That(variableNames.Contains("A2"), Is.True);
        }

        /// <summary>
        /// Tests <see cref="ExpressionTree"/> method <see cref="ExpressionTree.GetVariableNames()"/>
        /// by instantiating an <see cref="ExpressionTree"/> class, leaving it empty, and
        /// validating the output.
        /// </summary>
        [Test]
        public void ExpressionTreeGetVariableNamesEdge()
        {
            ExpressionTree tree = new ExpressionTree(string.Empty);
            List<string> variableNames = tree.GetVariableNames();
            Assert.That(variableNames, Is.Empty);
        }
    }
}
