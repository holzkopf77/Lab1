#ifndef LIST__HH
#define LIST__HH
#include <string>
#include <iostream>
#include "NodeL.hh"
#include <vector>
#include "iLista.hh"
#include "iObserwowany.hh"
#include "Obserwator.hh"
/**********************************************************************************/


/*!
 * \brief klasa List sluzy do wykonywania podstawowych operacji na Liscie:
 * dodaj,odejmij element. Przechowuje informacje o ilosci wszysktich elementow.
 */
template<typename T>
class List:public iList<T>,public iObserwowany<T>
{
public:
  std::vector<Obserwator<T>*> Obserwatorzy;
  long int RozmiarTestowanychDanych;
  long int StopCzas;
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
  void pop();
/*!
 *brief Funkcja dodaje element na koniec listy
 */
  void push_back(T value);
/*!
 *brief Funkcja zdejmuje element z konca listy
 */
  void pop_back();
/*!
 *brief Funkcja pokazujaca na strumieniu std::cout zawartosc listy
 */
  void show();
  /*!
   *brief Funkcja pokazujaca na strumieniu std::cout zawartosc listy od konca
   */
  void showOdKonca();
  /*!
   *brief Funkcja dodaje element przed elementem o indeksie nr
   */
  void push(T value,int nr=0);
  void push( T value);
  /*!
   * Przeciazony operator indeksowania zwraca referencje do elementu o indeksie a
   */
  T& operator[](int a)
  {
    NodeL<T> *p=this->head;
    for(int i=0;i<a;++i)p=p->next;
    return (p->val);
  }
  void dodaj(Obserwator<T>* obserwator);
  void powiadom();
  void usun(Obserwator<T> *obserwator);
  void ZmienDaneTestowe(long int IloscTestowanychDane, long int CzasStopu);
  
};


/*!
 * Konstruktor bezparametryczny, ustawia parametry na 0
 */
template <typename T>
List<T>::List()
  {
    this->head=nullptr;
    this->tail=nullptr;
    this->_size=0;
    RozmiarTestowanychDanych=0;
    StopCzas=0;
  }

/*!
 * Destruktor, usuwa kolejne elementy listy zaczynajac od poczatku
 */
template <typename T>
List<T>::~List()
  {
    for(NodeL<T> *p; this->head!=nullptr; this->head=p)
      {
	p=this->head->next;
	delete this->head;
      }
  }

/*!
 *\return Funkcja zwraca wartosc rozmiaru listy
 */
template <typename T>
int List<T>::size()
  {
    return this->_size;
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
    p->next=this->head;
    p->prev=nullptr;
    if(size())this->head->prev=p;
    this->head=p;// nowy poczatek listy
    if(!(size()))this->tail=this->head;
    ++this->_size;
  }

/*!
 *Funkcja sluzy do dodania elementu na poczatek listy
 *\param[in] value-typ int, wartosc elementu zmiennej dodanej do listy
 */
template <typename T>
void  List<T>::push(T value)
  {
    NodeL<T> *p=new NodeL<T>;
    p->val=value;
    p->next=this->head;
    p->prev=nullptr;
    if(size())this->head->prev=p;
    this->head=p;// nowy poczatek listy
    if(!(size()))this->tail=this->head;
    ++this->_size;
  }

/*!
 *Funkcja usuwa element z poczatku listy
 *\pre Lista nie moze byc pusta
 */
template <typename T>
void List<T>::pop_front()
  {
    NodeL<T> *p=this->head;
    if(p!=nullptr)
      {
	this->head=p->next;
	this->head->prev=nullptr;
	delete p;
	--this->_size;
      }
    else
      throw std::string("Lista pusta, ogarnij sie");
  }

/*!
 *Funkcja usuwa element z poczatku listy
 *\pre Lista nie moze byc pusta
 */
template <typename T>
void List<T>::pop()
  {
    NodeL<T> *p=this->head;
    if(p!=nullptr)
      {
	this->head=p->next;
	this->head->prev=nullptr;
	delete p;
	--this->_size;
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
  p = this->head;
  if(p!=nullptr) //jeśli lista nie jest pusta
  {
     while(p->next!=nullptr) p = p->next; //szukam końca listy
     p->prev=p;
     p->next = n; //wstawiam na końcowy zamiast nullptr
     this->tail=n;
  }
  else {this->head = n;this->tail=this->head;}
  ++this->_size;
}

/*!
 * Funkcja dodaje element przed elementem o indeksie nr
 * \param[in] value-wybrany typ, wartosc elementu dodanego do listy
 * \param[in] nr- indeks elementu przed ktorym ma byc dodany element
 * \pre indeksowanie od 0
 */  
template<typename T>
void List<T>::push(T value,int nr)
{
  NodeL<T> *p,*n;
  int licznik=0;
  n= new NodeL<T>;
  n->val=value;
  p=this->head;
  if(p!=nullptr && nr)
    {
      if(size()<nr)throw std::string("Operacja niemozliwa,lista jest za krotka");
      for(;licznik<nr-1 || p==nullptr;++licznik)
	p=p->next;
      n->next=p->next;
      p->next=n;
    }
  else if(p!=nullptr)
    {
    n->val=value;
    n->next=this->head;
    this->head=n;// nowy poczatek listy
    }
  else{
       n->next=nullptr;
       this->head=n;
       }
  ++this->_size;
}

/*!
 *Funkcja usuwa element z konca listy
 *\pre Lista nie moze byc pusta
 */
template <typename T>
void List<T>::pop_back()
{
  NodeL<T> * p = this->head;
  if(p!=nullptr)
  {
    if(p->next!=nullptr) //usuwanie jeśli jest więcej elementów niż tylko startowy
    {
      while(p->next->next!=nullptr) p = p->next; // szukam przedostatniego z listy
      this->tail=this->tail->prev;
      delete p->next; //usuwam ostatniego
      p->next = nullptr; //oznaczam nowy koniec listy
    }
    else
    {
      delete p;  
      this->head = nullptr; // lista staje się listą pustą
      this->tail=nullptr;
    }
  }
  else
    {
      throw std::string("Ogarnij sie, lista jest pusta");
    }
  --this->_size;
}
  
/*!
 *Funkcja wyswietla elementy listy
 */
template <typename T>
void List<T>::show()
{
  NodeL<T>* p=this->head;
  for(int i=0;i<this->_size;++i)
    {
      std::cout<<p->val<<" ";
      p=p->next;
    }
}

/*!
 *Funkcja wyswietla elementy listy od konca
 */
template <typename T>
void List<T>::showOdKonca()
{
  std::cout<<"and"<<std::endl;
  NodeL<T>* p=this->tail;
  for(int i=0;i<this->_size;++i)
    {
      std::cout<<p->val<<" ";
      p=p->prev;
    }
}

template <typename T>
void List<T>::dodaj(Obserwator<T>* obserwator)
{
  Obserwatorzy.push_back(obserwator);
}
template <typename T>
void List<T>::usun(Obserwator<T>* obserwator)
{
  Obserwatorzy.pop_back();
}

template <typename T>
void List<T>::powiadom()
{
  for(int i=0;i<Obserwatorzy.size();++i)
      Obserwatorzy[i]->odswiez(RozmiarTestowanychDanych,StopCzas);
}

template<typename T>
void List<T>::ZmienDaneTestowe(long int IloscTestowanychDanych, long int CzasStopu)
{
  RozmiarTestowanychDanych=IloscTestowanychDanych;
  StopCzas=CzasStopu;
}

#endif
