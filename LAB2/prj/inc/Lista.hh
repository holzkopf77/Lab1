#ifndef LIST__HH
#define LIST__HH

/**********************************************************************************/
/*!
 * \file
 * \brief Struktura przechowujaca wartosc wezla i wskaznik na
 * nastepny element typu Node
 */
template<typename T>
struct  NodeL
{
  T  val;
  NodeL<T> * next;
};


/*!
 * \brief klasa List sluzy do wykonywania podstawowych operacji na Liscie:
 * dodaj,odejmij element. Przechowuje informacje o ilosci wszysktich elementow.
 */
template<typename T>
class List
{
/*!
 *brief wskaznik do ktorego doczepione sa kolejne elementy
 */
  NodeL<T> *head;
/*!
 *brief Informacja o rozmiarze listy
 */
  int _size;
public:
/*!
 *brief Konstruktor bezparametryczny
 */
  List();
/*!
 *brief Destruktor
 */
  ~List();
/*!
 *brief Funkcja zwraca rozmiar listy
 */
  int size();
/*!
 *brief Funkcja dodaje element na poczatek listy
 */
  void  push_front(T value);
/*!
 *brief Funkcja zdejmuje element z poczatku listy
 */
  void pop_front();
/*!
 *brief Funkcja dodaje element na koniec listy
 */
  void push_back(T value);
/*!
 *brief Funkcja zdejmuje element z konca listy
 */
  void pop_back();
/*!
 *brief Funkcja wyswietla wszystkie elementy na standardowe wyjscie
 */
  void show();
};


/*!
 * Konstruktor bezparametryczny, ustawia parametry na 0
 */
template <typename T>
List<T>::List()
  {
    head=nullptr;
    _size=0;
  }

/*!
 * Destruktor, usuwa kolejne elementy listy zaczynajac od poczatku
 */
template <typename T>
List<T>::~List()
  {
    for(NodeL<T> *p; head!=nullptr; head=p)
      {
	p=head->next;
	delete head;
      }
  }

/*!
 *\return Funkcja zwraca wartosc rozmiaru listy
 */
template <typename T>
int List<T>::size()
  {
    return _size;
  }
  
/*!
 *Funkcja sluzy do dodania elementu na poczatek listy
 *\param[in] value-typ int, wartosc elementu zmiennej dodanej do listy
 */
template <typename T>
void  List<T>::push_front(T value)
  {
    NodeL<T> *p=new NodeL<T>;
    p->val=value;
    p->next=head;
    head=p;// nowy poczatek listy
    ++_size;
  }

/*!
 *Funkcja usuwa element z poczatku listy
 *\pre Lista nie moze byc pusta
 */
template <typename T>
void List<T>::pop_front()
  {
    NodeL<T> *p=head;
    if(p!=nullptr)
      {
	head=p->next;
	delete p;
	--_size;
      }
    else
      throw std::string("Lista pusta, ogarnij sie");
  }

/*!
 *Funkcja dodaje element na koniec listy
 *\param[in] value - typ int, wartosc elementu dodanego na koniec listy
 */
template <typename T>
void List<T>::push_back(T value)
{
  NodeL<T> * p, * n;
  n = new NodeL<T>;  // tworze nowy element
  n->next = nullptr;   // będzie wyznaczał koniec listy
  n->val = value;       //I przechowywał podaną wartość
  p = head;
  if(p!=nullptr) //jeśli lista nie jest pusta
  {
     while(p->next!=nullptr) p = p->next; //szukam końca listy
     p->next = n; //wstawiam na końcowy zamiast nullptr
  }
  else head = n;
  ++_size;
}
  
/*!
 *Funkcja usuwa element z konca listy
 *\pre Lista nie moze byc pusta
 */
template <typename T>
void List<T>::pop_back()
{
  NodeL<T> * p = head;
  if(p!=nullptr)
  {
    if(p->next!=nullptr) //usuwanie jeśli jest więcej elementów niż tylko startowy
    {
      while(p->next->next!=nullptr) p = p->next; // szukam przedostatniego z listy
      delete p->next; //usuwam ostatniego
      p->next = nullptr; //oznaczam nowy koniec listy
    }
    else
    {
      delete p;  
      head = nullptr; // lista staje się listą pustą
    }
  }
  else
    {
      throw std::string("Ogarnij sie, lista jest pusta");
    }
  --_size;
}
  
/*!
 *Funkcja wyswietla elementy listy
 */
template <typename T>
void List<T>::show()
{
  NodeL<T>* p=head;
  for(int i=0;i<_size;++i)
    {
      std::cout<<p->val<<" ";
      p=p->next;
    }
}

#endif
