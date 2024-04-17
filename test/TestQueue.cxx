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

    EXPECT_TRUE(header.isEmpty());
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

TEST(TestQueue, InsertMultipleBackward)
{
    QueueHead<int> header;
    Node<int> *node = nullptr;

    EXPECT_TRUE(header.isEmpty());
    for (int ii = 0; ii < 10; ii++)
    {
        node = new Node<int>(ii);
        header.push_backward(node);
    }
    EXPECT_FALSE(header.isEmpty());
    node = nullptr;
    node = header.forward();
    int ii = 0;
    while (!(header == node))
    {
        EXPECT_EQ(ii, node->getData());
        ii++;
        node = node->forward();
    }
}

TEST(TestQueue, InsertMultipleBoth)
{
    QueueHead<int> header;
    Node<int> *node = nullptr;

    EXPECT_TRUE(header.isEmpty());
    for (int ii = 0; ii < 10; ii++)
    {
        node = new Node<int>(ii);
        if ((ii % 2) == 0)
        {
            header.push_backward(node);
        }
        else
        {
            header.push_forward(node);
        }
    }
    EXPECT_FALSE(header.isEmpty());
    node = nullptr;
    node = header.backward();
    int jj = 8;
    bool increment = false;
    for (int ii = 0; ii < 10; ii++)
    {
        EXPECT_EQ(jj, node->getData());
        if (jj == 0)
        {
            jj = 1;
            increment = true;
        }
        else
        {
            jj += (increment ? 2 : -2);
        }
        node = node->backward();
    }
}

TEST(TestQueue, InsertPopForward)
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
    node = header.pop_forward();
    EXPECT_EQ(9, node->getData());
    node = header.forward();
    for (int ii = 8; ii >= 0; ii--)
    {
        EXPECT_EQ(ii, node->getData());
        node = node->forward();
    }
}

TEST(TestQueue, InsertPopBackward)
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
    node = header.pop_backward();
    EXPECT_EQ(0, node->getData());
    node = header.forward();
    for (int ii = 9; ii < 0; ii--)
    {
        EXPECT_EQ(ii, node->getData());
        node = node->forward();
    }
}

TEST(TestQueue, PopTillEmpty)
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
    node = header.pop_forward();
    EXPECT_EQ(9, node->getData());
    int jj = 8;
    while (!header.isEmpty())
    {
        node = header.pop_forward();
        EXPECT_EQ(jj, node->getData());
        jj--;
    }
}

TEST(TestNode, ClassInit)
{
    Node<int> node;

    EXPECT_TRUE(node.isUnlinked());
}

TEST(TestNode, IsConditionals)
{
    QueueHead<int> head;
    Node<int> *node = new Node<int>(1122);

    EXPECT_TRUE(node->isUnlinked());
    EXPECT_FALSE(node->isOnly(&head));
    head.push_forward(node);
    EXPECT_FALSE(node->isUnlinked());
    EXPECT_TRUE(node->isOnly(&head));
    node = nullptr;
    node = head.pop_backward();
    ASSERT_TRUE(node != nullptr);
    delete node;
    node = nullptr;
}

TEST(TestNode, Forward)
{
    QueueHead<int> header;
    Node<int> *node = nullptr;

    for (int ii = 0; ii < 10; ii++)
    {
        node = new Node<int>(ii);
        header.push_forward(node);
    }
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

TEST(TestNode, Backward)
{
    QueueHead<int> header;
    Node<int> *node = nullptr;

    for (int ii = 0; ii < 10; ii++)
    {
        node = new Node<int>(ii);
        header.push_backward(node);
    }
    node = nullptr;
    node = header.forward();
    int ii = 0;
    while (!(header == node))
    {
        EXPECT_EQ(ii, node->getData());
        ii++;
        node = node->forward();
    }
}

TEST(TestNode, Insque)
{
    QueueHead<int> header;
    Node<int> *node = nullptr;
    Node<int> *newNode = new Node<int>(42);

    for (int ii = 0; ii < 10; ii++)
    {
        node = new Node<int>(ii);
        header.push_forward(node);
    }
    node = nullptr;
    node = header.forward();
    while (node->getData() != 5)
    {
        node = node->forward();
    }
    node = node->insque(newNode);
    node = header.forward();
    int ii = 9;
    bool next42 = false;
    while (header != node)
    {
        if (next42)
        {
            EXPECT_EQ(42, node->getData());
            next42 = false;
        }
        else
        {
            EXPECT_EQ(ii, node->getData());
            ii--;
            if (5 == node->getData())
            {
                next42 = true;
            }
        }
        node = node->forward();
    }
}

TEST(TestNode, Remque)
{
    QueueHead<int> header;
    Node<int> *node = nullptr;
    Node<int> *newNode = new Node<int>(42);

    for (int ii = 0; ii < 10; ii++)
    {
        node = new Node<int>(ii);
        header.push_forward(node);
    }
    node = nullptr;
    node = header.forward();
    while (node->getData() != 5)
    {
        node = node->forward();
    }
    node = node->insque(newNode);
    node = header.forward();
    int ii = 9;
    bool next42 = false;
    while (header != node)
    {
        if (next42)
        {
            EXPECT_EQ(42, node->getData());
            next42 = false;
            node = node->backward();
            newNode = node->forward()->remque();
            EXPECT_TRUE(newNode->isUnlinked());
            delete newNode;
            newNode = nullptr;
        }
        else
        {
            EXPECT_EQ(ii, node->getData());
            ii--;
            if (5 == node->getData())
            {
                next42 = true;
            }
        }
        node = node->forward();
    }
    node = header.forward();
    ii = 9;
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
