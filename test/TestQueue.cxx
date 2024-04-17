//
// Copyright (C) Jonathan D. Belanger 2024.
// All Rights Reserved.
//
// This software is furnished under a license and may be used and copied only in accordance with the terms of such
// license and with the inclusion of the above copyright notice.  This software or any other copies thereof may not be
// provided or otherwise made available to any other person.  No title to and ownership of the software is hereby
// transferred.
//
// The information in this software is subject to change without notice and should not be construed as a commitment by
// the author or co-authors.
//
// The author and any co-authors assume no responsibility for the use or reliability of this software.
//
// Description:
//
//! @file
//  This file contains the code to fully test the Queue functionality.
//
// Revision History:
//
//  V01.000 16-Apr-2024 Jonathan D. Belanger
//  Initially written.
//
#include "Queue.hxx"
#include <gtest/gtest.h>

TEST(TestQueue, ClassInit)
{
    QueueHead<int> header;
    Node<int> node;

    EXPECT_TRUE(header.isEmpty());
    EXPECT_TRUE(node.isUnlinked());
}

TEST(TestQueue, InsertForward)
{
    QueueHead<int> header;
    Node<int> *node = new Node<int>(42);

    EXPECT_TRUE(header.isEmpty());
    EXPECT_TRUE(node->isUnlinked());
    header.push_forward(node);
    EXPECT_FALSE(header.isEmpty());
    EXPECT_FALSE(node->isUnlinked());
    node = nullptr;
    node = header.forward();
    EXPECT_EQ(42, node->getData());
}

TEST(TestQueue, InsertBackward)
{
    QueueHead<int> header;
    Node<int> *node = new Node<int>(314);

    EXPECT_TRUE(header.isEmpty());
    EXPECT_TRUE(node->isUnlinked());
    header.push_backward(node);
    EXPECT_FALSE(header.isEmpty());
    EXPECT_FALSE(node->isUnlinked());
    node = nullptr;
    node = header.backward();
    EXPECT_EQ(314, node->getData());
}

TEST(TestQueue, InsertMultipleForward)
{
    QueueHead<int> header;
    Node<int> *node = nullptr;

    EXPECT_TRUE(header.isEmpty());
    for (int ii = 0; ii < 10; ii++)
    {
        node = new Node<int>(ii);
        header.push_forward(node);
    }
    EXPECT_FALSE(header.isEmpty());
    node = nullptr;
    node = header.forward();
    int ii = 9;
    while (header != node)
    {
        EXPECT_EQ(ii, node->getData());
        ii--;
        node = node->forward();
    }
}

int
main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
