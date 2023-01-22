// <copyright file="UnitTest1.cs" company="Killian Griffin">
// Copyright (c) Killian Griffin. All rights reserved.
// </copyright>

namespace HW3.Test
{
    using System.Numerics;
    using NUnit.Framework;

    /// <summary>
    /// Test class for testing the functionality of the
    /// <see cref="FibonacciTextReader"/> class.
    /// </summary>
    public class UnitTest1
    {
        /// <summary>
        /// Tests the <see cref="FibonacciTextReader.ReadLine()"/> method
        /// by assering that the return value after being called 16 times is
        /// a string representation of the 16th number in the Fibonacci
        /// sequence, 987.
        /// </summary>
        [Test]
        public void TestFibonacciReadLineNormal()
        {
            FibonacciTextReader fibonacciTest = new FibonacciTextReader(50);
            for (int i = 0; i < 15; ++i)
            {
                fibonacciTest.ReadLine();
            }

            Assert.That(fibonacciTest.ReadLine(), Is.EqualTo("987"));
        }

        /// <summary>
        /// Tests the <see cref="FibonacciTextReader.ReadToEnd()"/> method
        /// by asserting that the method returns a string representation of
        /// numbers in the Fibonacci sequence 1 - 8 when given a maximum
        /// sequence length of 8.
        /// </summary>
        [Test]
        public void TestFibonacciReadToEndNormal()
        {
            FibonacciTextReader fibonacciTest = new FibonacciTextReader(8);
            string eighthFibonacciString =
                "1. 1\r\n" +
                "2. 1\r\n" +
                "3. 2\r\n" +
                "4. 3\r\n" +
                "5. 5\r\n" +
                "6. 8\r\n" +
                "7. 13\r\n" +
                "8. 21\r\n";
            Assert.That(fibonacciTest.ReadToEnd, Is.EqualTo(eighthFibonacciString));
        }

        /// <summary>
        /// Tests the <see cref="FibonacciTextReader.ReadLine()"/> method
        /// by asserting that the method returns null after being called
        /// more than the maximum sequence length.
        /// </summary>
        [Test]
        public void TestFibonacciReadLineNullOnMaxSequence()
        {
            FibonacciTextReader fibonacciTest = new FibonacciTextReader(10);
            for (int i = 0; i < 10; ++i)
            {
                fibonacciTest.ReadLine();
            }

            Assert.That(fibonacciTest.ReadLine(), Is.EqualTo(string.Empty));
        }

        /// <summary>
        /// Tests the <see cref="FibonacciTextReader.ReadToEnd()"/> method
        /// with large numbers. It asserts that the method returns a string
        /// containing the 100th Fibonacci number when given a maximum sequence
        /// length of 100.
        /// </summary>
        [Test]
        public void TestFibonacciReadToEndLargeSequence()
        {
            FibonacciTextReader fibonacciTest = new FibonacciTextReader(100);

            // split on "100. " gets the last element of the 100 sequence string
            string fibonacciString = fibonacciTest.ReadToEnd().Split("100. ")[1];

            // taking the substring index 0-21 removes the newline from the sequence string
            Assert.That(fibonacciString.Substring(0, 21), Is.EqualTo("354224848179261915075"));
        }

        /// <summary>
        /// Tests the <see cref="FibonacciTextReader.ReadLine()"/> method
        /// by asserting that the first call of the method returns a string
        /// representation of the first number in the Fibonacci sequence, 1.
        /// </summary>
        [Test]
        public void TestFibonacciReadLineFirstCall()
        {
            FibonacciTextReader fibonacciTest = new FibonacciTextReader(10);
            Assert.That(fibonacciTest.ReadLine(), Is.EqualTo("1"));
        }

        /// <summary>
        /// Tests the <see cref="FibonacciTextReader.ReadToEnd()"/> method
        /// by asserting that the method returns an empty string when given
        /// a 0 max sequence number.
        /// </summary>
        [Test]
        public void TestFibonacciReadToEndZero()
        {
            FibonacciTextReader fibonacciTest = new FibonacciTextReader(0);
            Assert.That(fibonacciTest.ReadToEnd(), Is.EqualTo(string.Empty));
        }
    }
}