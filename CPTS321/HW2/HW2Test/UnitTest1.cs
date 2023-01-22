// <copyright file="UnitTest1.cs" company="Killian Griffin">
// Copyright (c) Killian Griffin. All rights reserved.
// </copyright>

namespace HW2.Test
{
    using System.Collections.Generic;
    using NUnit.Framework;

    /// <summary>
    /// Contains tests for the three distinct integer menthods
    /// (<see cref="DistinctIntegersCalculator.InPlace(List{int})"/>,
    /// <see cref="DistinctIntegersCalculator.InPlace(List{int})"/>, and <see cref="DistinctIntegersCalculator.Sort(List{int})"/>).
    /// </summary>
    [TestFixture]
    internal class UnitTest1
    {
        /// <summary>
        /// Tests the method
        /// <see cref="DistinctIntegersCalculator.HashSet(List{int}))"/>
        /// by passing a fixed <see cref="List{int}"/> and asserting the output is
        /// equal to the number of distinct integers in the list.
        /// </summary>
        [Test]
        public void TestDistinctIntegersHashSet()
        {
            List<int> testList = new List<int>();
            testList.AddRange(new[] { 1, 2, 1, 1, 3, 2, 50, 3, 4 });
            Assert.That(DistinctIntegersCalculator.HashSet(new List<int>(testList)), Is.EqualTo(5));
        }

        /// <summary>
        /// Tests the method
        /// <see cref="DistinctIntegersCalculator.InPlace(List{int})(List{int})"/>
        /// by passing a fixed <see cref="List{int}"/> and asserting the output is
        /// equal to the number of distinct integers in the list.
        /// </summary>
        [Test]
        public void TestDistinctIntegersInPlace()
        {
            List<int> testList = new List<int>();
            testList.AddRange(new[] { 3, 2, 3, 30, 34, 22, 30, 2, 2, 4, 1 });
            Assert.That(DistinctIntegersCalculator.InPlace(new List<int>(testList)), Is.EqualTo(7));
        }

        /// <summary>
        /// Tests the method
        /// <see cref="DistinctIntegersCalculator.Sort(List{int})"/>
        /// by passing a fixed <see cref="List{int}"/> and asserting the output is
        /// equal to the number of distinct integers in the list.
        /// </summary>
        [Test]
        public void TestDistinctIntegersSort()
        {
            List<int> testList = new List<int>();
            testList.AddRange(new[] { 5, 2, 3, 1, 5, 3, 2, 40, 23, 1 });
            Assert.That(DistinctIntegersCalculator.Sort(new List<int>(testList)), Is.EqualTo(6));
        }
    }
}