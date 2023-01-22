namespace SpreadsheetEngine.Test
{
    using System;
    using System.Collections.Generic;
    using NUnit.Framework;

    internal class PostfixExpressionConverterUnitTest
    {
        /// <summary>
        /// Tests <see cref="PostfixExpressionConverter"/> class by creating
        /// an instance and validating the output of the
        /// <see cref="PostfixExpressionConverter.PostfixConvert(string)"/> method.
        /// </summary>
        [Test]
        public void PostfixExpressionConverterNormalTest1()
        {
            string expression = "1+2*3";
            Dictionary<string, double> parameters = new Dictionary<string, double>();
            PostfixExpressionConverter testConverter = new PostfixExpressionConverter();
            List<Node> convertedExpression = testConverter.PostfixConvert(expression, ref parameters);

            Assert.That(convertedExpression[0].GetValue, Is.EqualTo(1));
            Assert.That(convertedExpression[1].GetValue, Is.EqualTo(2));
            Assert.That(convertedExpression[2].GetValue, Is.EqualTo(3));
            Assert.That(((OperatorNode)convertedExpression[3]).OperatorChar, Is.EqualTo('*'));
            Assert.That(((OperatorNode)convertedExpression[4]).OperatorChar, Is.EqualTo('+'));
        }

        /// <summary>
        /// Tests <see cref="PostfixExpressionConverter"/> class by creating
        /// an instance and validating the output of the
        /// <see cref="PostfixExpressionConverter.PostfixConvert(string)"/> method.
        /// </summary>
        [Test]
        public void PostfixExpressionConverterNormalTest2()
        {
            string expression = "4*2/3+4+4*3";
            Dictionary<string, double> parameters = new Dictionary<string, double>();
            PostfixExpressionConverter testConverter = new PostfixExpressionConverter();
            List<Node> convertedExpression = testConverter.PostfixConvert(expression, ref parameters);

            Assert.That(convertedExpression[0].GetValue, Is.EqualTo(4));
            Assert.That(convertedExpression[1].GetValue, Is.EqualTo(2));
            Assert.That(((OperatorNode)convertedExpression[2]).OperatorChar, Is.EqualTo('*'));
            Assert.That(convertedExpression[3].GetValue, Is.EqualTo(3));
            Assert.That(((OperatorNode)convertedExpression[4]).OperatorChar, Is.EqualTo('/'));
            Assert.That(convertedExpression[5].GetValue, Is.EqualTo(4));
            Assert.That(((OperatorNode)convertedExpression[6]).OperatorChar, Is.EqualTo('+'));
            Assert.That(convertedExpression[7].GetValue, Is.EqualTo(4));
            Assert.That(convertedExpression[8].GetValue, Is.EqualTo(3));
            Assert.That(((OperatorNode)convertedExpression[9]).OperatorChar, Is.EqualTo('*'));
            Assert.That(((OperatorNode)convertedExpression[10]).OperatorChar, Is.EqualTo('+'));
        }

        /// <summary>
        /// Tests <see cref="PostfixExpressionConverter"/> class by creating
        /// an instance and validating the output of the
        /// <see cref="PostfixExpressionConverter.PostfixConvert(string)"/> method.
        /// </summary>
        [Test]
        public void PostfixExpressionConverterNormalTest3()
        {
            string expression = "2-4-2/1*2+4";
            Dictionary<string, double> parameters = new Dictionary<string, double>();
            PostfixExpressionConverter testConverter = new PostfixExpressionConverter();
            List<Node> convertedExpression = testConverter.PostfixConvert(expression, ref parameters);

            Assert.That(convertedExpression[0].GetValue, Is.EqualTo(2));
            Assert.That(convertedExpression[1].GetValue, Is.EqualTo(4));
            Assert.That(((OperatorNode)convertedExpression[2]).OperatorChar, Is.EqualTo('-'));
            Assert.That(convertedExpression[3].GetValue, Is.EqualTo(2));
            Assert.That(convertedExpression[4].GetValue, Is.EqualTo(1));
            Assert.That(((OperatorNode)convertedExpression[5]).OperatorChar, Is.EqualTo('/'));
            Assert.That(convertedExpression[6].GetValue, Is.EqualTo(2));
            Assert.That(((OperatorNode)convertedExpression[7]).OperatorChar, Is.EqualTo('*'));
            Assert.That(((OperatorNode)convertedExpression[8]).OperatorChar, Is.EqualTo('-'));
            Assert.That(convertedExpression[9].GetValue, Is.EqualTo(4));
            Assert.That(((OperatorNode)convertedExpression[10]).OperatorChar, Is.EqualTo('+'));
        }

        /// <summary>
        /// Tests <see cref="PostfixExpressionConverter"/> class by creating
        /// an instance and validating the output of the
        /// <see cref="PostfixExpressionConverter.PostfixConvert(string)"/> method.
        /// </summary>
        [Test]
        public void PostfixExpressionConverterNormalTest4()
        {
            string expression = "2-(4-2)/1*2+4";
            Dictionary<string, double> parameters = new Dictionary<string, double>();
            PostfixExpressionConverter testConverter = new PostfixExpressionConverter();
            List<Node> convertedExpression = testConverter.PostfixConvert(expression, ref parameters);

            Assert.That(convertedExpression[0].GetValue, Is.EqualTo(2));
            Assert.That(convertedExpression[1].GetValue, Is.EqualTo(4));
            Assert.That(convertedExpression[2].GetValue, Is.EqualTo(2));
            Assert.That(((OperatorNode)convertedExpression[3]).OperatorChar, Is.EqualTo('-'));
            Assert.That(convertedExpression[4].GetValue, Is.EqualTo(1));
            Assert.That(((OperatorNode)convertedExpression[5]).OperatorChar, Is.EqualTo('/'));
            Assert.That(convertedExpression[6].GetValue, Is.EqualTo(2));
            Assert.That(((OperatorNode)convertedExpression[7]).OperatorChar, Is.EqualTo('*'));
            Assert.That(((OperatorNode)convertedExpression[8]).OperatorChar, Is.EqualTo('-'));
            Assert.That(convertedExpression[9].GetValue, Is.EqualTo(4));
            Assert.That(((OperatorNode)convertedExpression[10]).OperatorChar, Is.EqualTo('+'));
        }

        /// <summary>
        /// Tests <see cref="PostfixExpressionConverter"/> class by creating
        /// an instance and validating that the
        /// <see cref="PostfixExpressionConverter.PostfixConvert(string)"/> method
        /// throws an <see cref="ArgumentException"/> on invalid input.
        /// </summary>
        [Test]
        public void PostfixExpressionConverterExceptionTest()
        {
            string expression = "2-4|43";
            Dictionary<string, double> parameters = new Dictionary<string, double>();
            PostfixExpressionConverter testConverter = new PostfixExpressionConverter();
            Assert.Throws<ArgumentException>(() => testConverter.PostfixConvert(expression, ref parameters));
        }
    }
}
