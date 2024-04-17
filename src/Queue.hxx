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
//  This file contains the template class definitions to support utilizing a doubly-liked queue.
//
// Revision History:
//
//  V01.000 16-Apr-2024 Jonathan D. Belanger
//  Initially written.
//
#pragma once

template <class T>
class QueueHead;

template <class T>
class Node
{
    public:
        friend class QueueHead<T>;
        explicit Node() :
            flink(this),
            blink(this),
            nodeData()
        {}

        explicit Node(T data) :
            flink(this),
            blink(this),
            nodeData(data)
        {}

        ~Node() = default;

        Node(const Node&) = delete;

        Node& operator=(const Node&) = delete;

        bool
        isUnlinked()
        {
            return ((flink == this) && (blink == this));
        }

        Node<T>*
        forward()
        {
            return flink;
        }

        Node<T>*
        backward()
        {
            return blink;
        }

        void
        insque(Node<T>* node)
        {
            node->flink = flink;
            node->blink = this;
            flink->blink = node;
            flink = node;
        }

        Node<T>*
        remque()
        {
            flink->blink = blink;
            blink->flink = flink;
            flink = this;
            blink = this;
            return this;
        }

        T
        getData()
        {
            return nodeData;
        }

    private:
        Node<T>* flink;
        Node<T>* blink;
        T nodeData;
};

template <class T>
class QueueHead : private Node<T>
{
    public:
        friend class Node<T>;
        explicit QueueHead() :
            flink(this),
            blink(this)
        {}

        ~QueueHead() = default;

        QueueHead(const QueueHead&) = delete;

        QueueHead&
        operator=(const QueueHead&) = delete;

        bool
        equal(const Node<T>* node)
        {
            return (this == node);
        }

        void
        push_forward(Node<T>* node)
        {
            if (isEmpty())
            {
                node->flink = this;
                node->blink = this;
                flink = node;
                blink = node;
            }
            else
            {
                node->flink = flink;
                node->blink = this;
                flink->blink = node;
                flink = node;
            }
        }

        void
        push_backward(Node<T>* node)
        {
            if (isEmpty())
            {
                node->flink = this;
                node->blink = this;
                flink = node;
                blink = node;
            }
            else
            {
                node->flink = this;
                node->blink = blink;
                blink->flink = node;
                blink = node;
            }
        }

        Node<T>*
        pop_forward()
        {
            if (!isEmpty())
            {
                Node<T>* node = flink;

                flink = node->flink;
                node->flink->blink = this;
                node->flink = node;
                node->blink = node;
                return node;
            }
            return nullptr;
        }

        Node<T>*
        pop_backward()
        {
            if (!isEmpty())
            {
                Node<T>* node = blink;

                node->blink->flink = this;
                blink = node->blink;
                node->flink = node;
                node->blink = node;
                return node;
            }
            return nullptr;
        }

        bool
        isEmpty()
        {
            return ((flink == this) && (blink == this));
        }

        Node<T>*
        forward()
        {
            return flink;
        }

        Node<T>*
        backward()
        {
            return blink;
        }

    private:
        Node<T>* flink;
        Node<T>* blink;
};
