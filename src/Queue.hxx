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

//
// Forward declaration of the QueueHead.
//
template <class T>
class QueueHead;

//
//! @class Node
//  @brief Node The following template class is used for a single item in a doubly-linked list (queue).
//  @tparam T Type of the data to be stored in a Node
//  @note This class is not thread-safe.
//
template <class T>
class Node
{
    public:
        friend class QueueHead<T>;

        //
        //! @fn Node()
        //  @brief Default Constructor
        //
       explicit Node() :
            flink(this),
            blink(this),
            nodeData()
        {}

       //
       //! @fn Node()
       //  @brief Constructor with Data
       //
        explicit Node(T data) :
            flink(this),
            blink(this),
            nodeData(data)
        {}

        //
        //! @fn ~Node()
        //  @brief Default Destructor
        //
        ~Node() = default;

        //
        //! @fn Node(const Node&)
        //  @brief Disable the ability to copy this class via another Node.
        //  @param Node A reference to a Node.
        //
        Node(const Node&) = delete;

        //
        //! @fn Node& operator=(Node&)
        //  @brief Disable the ability to copy this class via the equal operator.
        //  @param Node A reference to a Node.
        //  @retval Node A reference to a Node.
        //
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
        Node<T>* flink;             //!< Forward link to the next node in the queue (or the header, or itself).
        Node<T>* blink;             //!< Backward link to the previous node in the queue (or the header, or itself).
        T nodeData;                 //!< The data of the Node class.
};

//
//! @class QueueHead
//  @brief A header for a doubly-linked list (queue) of Node items.
//  @tparam T The class of the data to be stored in the queue.
//  @note This class is not thread-safe.
//
template <class T>
class QueueHead : private Node<T>
{
    public:
        friend class Node<T>;

        //
        //! @fn QueueHead()
        //  @brief Default Constructor
        //
        explicit QueueHead() :
            flink(this),
            blink(this)
        {}

        //
        //! @fn ~QueueHead()
        //  @brief Default Destructor
        //
        ~QueueHead() = default;

        //
        //! @fn QueueHead(const QueueHead &)
        //  @brief Disable the ability to copy this class via another QueueHead.
        //  @param QueueHead A reference to a QueueHead.
        //
        QueueHead(const QueueHead&) = delete;

        //
        //! @fn QueueHead& operator=(QueueHead &)
        //  @brief Disable the ability to copy this class via the equal operator.
        //  @param QueueHead A reference to a QueueHead.
        //  @retval QueueHead A reference to a QueueHead.
        //
        QueueHead&
        operator=(const QueueHead&) = delete;

        bool
        operator==(const Node<T>* node)
        {
            return static_cast<void*>(this) == static_cast<const void*>(node);
        }
        bool

        operator!=(const Node<T>* node)
        {
            return static_cast<void*>(this) != static_cast<const void*>(node);
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
        Node<T>* flink;             //!< Forward link to the first node in the queue (or the header).
        Node<T>* blink;             //!< Backward link to the last node in the queue (or the header).
};
