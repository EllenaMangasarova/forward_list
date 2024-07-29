#include "ForwardList.h"

ForwardList::ForwardList()
    : FHead(nullptr)
{

}

ForwardList::ForwardList(const ForwardList& AOth)
    : FHead(nullptr)
{
    Copy(AOth);
}

ForwardList::ForwardList(ForwardList&& AOth)
    : FHead(AOth.FHead)
{
    AOth.FHead = nullptr;
}

ForwardList::~ForwardList()
{
    Clear();
}

ForwardList ForwardList::operator=(const ForwardList& ARhs)
{
    if (this == &ARhs) { return *this; }

    Clear();
    Copy(ARhs);

    return *this;
}

ForwardList ForwardList::operator=(ForwardList&& ARhs)
{
    if (this == &ARhs) { return *this; }

    Clear();
    FHead = ARhs.FHead;
    ARhs.FHead = nullptr;
    
    return *this;
}

void ForwardList::Copy(const ForwardList& AOth)
{
    if (AOth.Empty()) { return; }

    Node* oth_head = AOth.FHead;
    FHead = new Node(oth_head->Value);
    Node* tmp = FHead;
    oth_head = oth_head->Next;
    while (oth_head) {
        tmp->Next = new Node(oth_head->Value);
        tmp = tmp->Next;
        oth_head = oth_head->Next;
    }
}

void ForwardList::Clear()
{
    Node* node = FHead;
    while (node) {
        Node* tmp = node->Next;
        delete node;
        node = tmp;
    }
    FHead = nullptr;
}

void ForwardList::PushFront(int AValue)
{
    FHead = (FHead ? new Node(AValue, FHead) : new Node(AValue));
}

void ForwardList::PopFront()
{
    if (!FHead) { return; }

    Node* tmp = FHead;
    FHead = FHead->Next;
    delete tmp;
}

bool ForwardList::Empty() const
{
    return !FHead;
}

ForwardList::Iterator ForwardList::InsertAfter(ForwardList::Iterator APos, int AValue)
{
    Node* tmp = APos.FElem;
    tmp->Next = new Node(AValue, tmp->Next);
    return ++APos;
}

void ForwardList::EraseAfter(ForwardList::Iterator APos)
{
    Node* del = APos.FElem->Next;
    if (!del) { return; }

    APos.FElem->Next = del->Next;
    delete del;
}

ForwardList::Iterator ForwardList::Begin()
{
    return Iterator(FHead);
}

ForwardList::Iterator ForwardList::End()
{
    return Iterator();
}