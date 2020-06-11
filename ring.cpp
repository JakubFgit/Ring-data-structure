#include <iostream>

using namespace std;

template <typename Key, typename Info>
class Ring {

	struct Element {
		Key	 k;
		Info i;
		Element* next;
		Element* prev;
	};
	Element* any;
	int count1;
public:
    Ring();
    ~Ring();
    Ring(const Ring<Key, Info> &Ring);
    int length()const;
    void clear_ring();
    void print();
    bool add_next_component(const Key&k, const Info&i);
    bool addPrev(const Key&k, const Info&i);
    bool insert_after(const Key& k, const Info& i, const Key& after);
    void remove_elem(const Key&kold, bool each);
    const Ring<Key,Info>&operator=(const Ring<Key,Info>&otherList);
    friend ostream&operator<<(ostream&o,const Ring<Key,Info>&s){print(); return 0;};
    Ring<Key, Info> operator+(const Ring<Key, Info>& ring1)const;
    friend Ring<Key,Info> & operator-(const Ring<Key, Info>& ring1, const Ring<Key, Info>& ring2)
    {

        Ring<Key, Info> *newRing = new Ring<Key, Info>;
		Ring<Key, Info>::iterator iter1 = ring1.begin();
		Ring<Key, Info>::iterator iter2 = ring2.begin();
		bool found = false;
		int length = ring1.length();
		while (length > 0)
		{
			iter2 = ring2.begin();
			do
			{
				if (iter1->k==iter2->k)
				{
					found = true;
				}
				if (found == true)
				{

					break;
				}
				++iter2;

			} while (ring2.begin() != iter2);
			if (found == false)
			{
				newRing->add_next_component(iter1.Elem_Key(), iter1.Elem_Info());
			}
			else
			{
				found = false;
			}
			length--;
			++iter1;
		}
		return *newRing;
}


class iterator{

        Element*node;
public:

        iterator(Element* copyElement) {node = copyElement;}
		iterator() { node = NULL; }
		iterator(const iterator& copy) { node = copy.node; *this = copy;}
		~iterator(){};
		iterator& operator=(const iterator& copy) { node = copy.node; return *this; }
		bool operator==(const iterator& compared) { return node == compared.node; }
		bool operator!=(const iterator& compared) { return node != compared.node; }
		iterator operator+(const unsigned int amount)
		{
			iterator newThis = *this;
			for (int i = 0; i<amount; i++)
				newThis++;
			return newThis;
		}
		iterator& operator++()
		{

			if (node != NULL)
			{
				node = node->next;
			}
			return *this;
		}

		iterator operator-(const unsigned int amount)
		{
			iterator newThis = *this;
			for (int i = 0; i<amount; i++)
				newThis--;
			return newThis;
		}

		iterator& operator--()
		{

			if (node != NULL)
			{
				node = node->prev;
			}
			return *this;
		}


        Element& operator*() { return *node; }
		Element* operator->() { return node; }
        Key Elem_Key() { return node->k; }
		Info Elem_Info() { return node->i; }

};
   iterator begin() const
	{
		if (any == NULL)
		{
			return NULL;
		}
		return iterator(any);
	}
	iterator end() const
	{
		if (any == NULL)
		{
			return NULL;
		}
		return iterator(any->prev);
	}



	};
template <typename Key, typename Info>
Ring<Key, Info>::Ring()
{
    any=NULL;
    count1=0;
}
template <typename Key, typename Info>
Ring<Key, Info>::~Ring()
{
    clear_ring();
}
template <typename Key, typename Info>
Ring<Key, Info>::Ring(const Ring<Key, Info> &Ring)
{
    this->any = NULL;
    if(Ring.any)
    {
        Element *current = Ring.any;
        do
        {
            this->add_next_component(current->k, current->i);
            current = current->next;
        }
        while(current != Ring.any);
    }
}
template <typename Key, typename Info>
int Ring<Key, Info>::length()const
{
    return count1;
}
template <typename Key, typename Info>
void  Ring<Key, Info> ::clear_ring()
{
    if (any == NULL)
        return;

    Element* ptr;
    any->prev->next = NULL;
    if (any != NULL)
        while (any != NULL)
        {
            ptr = any;
            any = any->next;
            delete ptr;
        }
    count1 = 0;
}
template <typename Key, typename Info>
bool Ring<Key, Info>::add_next_component(const Key&k, const Info&i)
{
        Element* new_el = new Element;
		new_el->k = k;
		new_el->i = i;

		if (any == NULL)
		{
			new_el->next = new_el;
			new_el->prev = new_el;
			any = new_el;
			count1++;
			return true;
		}
		else
		{
			new_el->next = any;
			new_el->prev = any->prev;
			any->prev->next = new_el;
			any->prev = new_el;
			count1++;
			return true;
		}
    return false;
}
template <typename Key, typename Info>
bool Ring<Key, Info>::addPrev(const Key&k, const Info&i)
{
        Element* new_el = new Element;
		new_el->k = k;
		new_el->i = i;

		if (any == NULL)
		{
			new_el->next = new_el;
			new_el->prev = new_el;
			any = new_el;
			count1++;
			return true;
		}
		else
		{
			new_el->prev = any;
			new_el->next = any->next;
			any->next->prev = new_el;
			any->next = new_el;
			count1++;
			return true;
		}
    return false;
}
template <typename Key, typename Info>
bool Ring<Key, Info>::insert_after(const Key& k, const Info& i, const Key& after)
{
        Element* new_el = new Element;
		new_el->k = k;
		new_el->i = i;
		Element* temp = any;
		if (any == NULL)
		{

			return false;
		}
		while (temp)
		{
			if (temp->k == after)
			{
				new_el->next = temp->next;
				new_el->prev = temp;
				temp->next->prev = new_el;
				temp->next = new_el;
				count1++;
				return true;
			}
			temp = temp->next;

		}
    return false;
}
template <typename Key, typename Info>
void Ring<Key, Info>::remove_elem(const Key&kold, bool each)
{
    int len1;
    len1 = length();
    Element* tab = any;
    Element* tab_2;

    while (any->k == kold){

        tab_2 = tab;
        tab->prev->next = tab_2->next;
        tab->next->prev = tab_2-> prev;
        any = tab->next;
        count1--;
        delete tab_2;
        if (each == false)
            return;
    }

    while (len1>0){

        if (each == true){

            if (tab->k == kold){

                tab_2 = tab;
                tab->prev->next = tab_2->next;
                tab->next->prev = tab_2->prev;
                tab = tab->next;
                delete tab_2;
                --count1;

            }

        tab = tab->next;

        }else

            if (tab->k == kold){

                tab_2 = tab;
                tab->prev->next = tab_2->next;
                tab->next->prev = tab_2->prev;
                tab = tab->next;
                delete tab_2;
                --count1;

                return;
            }
        tab = tab->next;
        len1--;


    }
}


template <typename Key, typename Info>
void Ring<Key, Info>::print()
{
        Element* temp = any;
		int counter = count1;
		if (temp == NULL)
		{
			cout << "Empty Ring" << endl;
			return;
		}
		do
		{
			cout <<temp->k<<"-->"<< temp->i << endl;
			temp = temp->next;
			counter--;
		} while(counter > 0);
}
template <typename Key, typename Info>
Ring<Key, Info> Ring<Key, Info>::operator + (const Ring<Key, Info> &ring1)const
{
    Ring<Key, Info> newRing; // create container Ring for sum
    Element *current = ring1.any;
    Element *temp = this->any;
    if(temp)
    {
        do
        {
            newRing.add_next_component(temp->k, temp->i); // insert content of the first ring
            temp = temp->next;
        }
        while(temp != any);
    }
    if(current)
    {
        do
        {
            //Node *temp;
            newRing.add_next_component(current->k, current->i); // insert content of the second ring
            current = current->next;
        }
        while(current != ring1.any);
    }
    return newRing;
}


template <typename Key, typename Info>
const Ring<Key, Info> &Ring<Key,Info>::operator=(const Ring<Key,Info>&otherRing)
{
if (&otherRing == this)
			return *this;
		int length = otherRing.length();

		clear_ring();
		Element* current = otherRing.any;
		while (length > 0)
		{
			add_next_component(current->k, current->i);
			current = current->next;
			length--;
		}
		return *this;
}
template<typename Key, typename Info>
Ring<Key, Info> produce(const Ring<Key, Info> &r1, int start1, int len1, bool dir1, const Ring<Key, Info> &r2, int start2, int len2, bool dir2, int repeat)
{

    typename Ring<Key, Info>::iterator iter1 = r1.begin();
    typename Ring<Key, Info>::iterator iter2 = r2.begin();
    Ring<Key, Info> r3;         //result ring
    if((len1 <= 0) || (len2 <= 0))
    {
        cout << "Wrong parameters" << endl;
        return r3;
    }
    for(int i=0; i<start1; i++) // set 1st Iterator on the start
        ++iter1;
    typename Ring<Key, Info>::iterator iterStart1 = iter1; // new end point for iter 1
    for(int i=0; i<start2; i++) // set 2nd Iterator on the start
        ++iter2;
    typename Ring<Key, Info>::iterator iterStart2 = iter2; // new end point for iter 2
    int counter = 0;
    {
        cout<<"Produced ring is empty"<<endl;
    }
        do // repetition loop
        {
            do // stop conditions loop
            {
                int i = 0;
                do  // 1st ring loop
                {
                    i++;
                    r3.add_next_component(iter1.Elem_Key(), iter1.Elem_Info());
                    if(dir1) // true- forward direction
                        ++iter1;
                    else
                        --iter1;
                }
                while((iter1 != iterStart1) && (i<len1));
                i = 0;
                do // 2nd ring loop
                {
                    i++;
                    r3.add_next_component(iter2.Elem_Key(), iter2.Elem_Info());
                    if(dir2) // true- forward direction
                        ++iter1;
                    else
                        --iter2; //false- backward direction
                }
                while((iter2 != iterStart2) && (i<len2));
            }
            while((iter1 != iterStart1) || (iter2 != iterStart2)); // stop when both rings meet their starts
                                        // ## stop when one of rings meet start -> && -> instead || ##
            counter++;
        }
        while(counter < repeat);
    return r3;
}

int main()
{
    Ring<int, int> r1, r2,r3,r4,r5,r6,r7,r8,r9,r10;
    r10.add_next_component(2,2);
    r10.add_next_component(1,1);
     r10.add_next_component(3,3);
    r10.add_next_component(2,2);
     r10.add_next_component(2,2);
     r10.add_next_component(2,2);
    r10.add_next_component(2,2);
    cout<<"R10:"<<endl;
    r10.print();
    r10.remove_elem(2, true);
    cout<<"R10 after removing:"<<endl;
    r10.print();



    return 0;
}
