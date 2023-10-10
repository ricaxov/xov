#include <bits/stdc++.h>
using namespace std;

// Jogo das Fichas - ED1

// Ficha {{{
class Ficha {
public:
  char player, color, tower;
  Ficha() : player('*'), color('*'), tower('*') {};
  Ficha(char p, char c, char t) : player(p), color(c), tower(t) {};
};
// }}}

// Node {{{
template<typename T> class Node {
public:
  T D;
  Node* Next;
  static Node* MontaNode(T X);
  static T DesmontaNode(Node<T>* Next);
};
template<typename T> Node<T>* Node<T>::MontaNode(T x) {
  Node* ptr = new Node;
  if(ptr) {
    ptr->D=x, ptr->Next=0;
  }
  return ptr;
}
template<typename T> T Node<T>::DesmontaNode(Node<T>* ptr) {
  T x;
  if(ptr) {
    x = ptr->D;
    delete ptr;
  }
  return x;
}
// }}}

// Stack {{{
template<typename T> class Stack {
public:
  int N;
  Node<T>* Top;
  Stack();
  ~Stack();
  bool push(T x);
  T pop();
  T top();
  int size();
  bool empty();
};
template<typename T> Stack<T>::Stack() {
  Top = 0, N = 0;
}
template<typename T> Stack<T>::~Stack() {
  Node<T>* ptr;
  while(Top) {
    ptr = Top;
    Top = Top->Next;
    Node<T>::DesmontaNode(ptr);
  }
}
template<typename T> bool Stack<T>::push(T x) {
  Node<T>* ptr = Node<T>::MontaNode(x);
  if(ptr == nullptr) return 0;
  ptr->Next = Top;
  Top = ptr, N++;
  return 1;
}
template<typename T> T Stack<T>::pop() {
  T x;
  if(Top) {
    Node<T>* ptr = Top;
    Top = ptr->Next;
    x = Node<T>::DesmontaNode(ptr);
    N--;
  }
  return x;
}
template<typename T> T Stack<T>::top() {
  T x;
  if(Top) x = Top->D;
  return x;
}
template<typename T> int Stack<T>::size() {
  return N;
}
template<typename T> bool Stack<T>::empty() {
  return !N;
}
// }}}

// Queue {{{
template<typename T> class Queue {
public:
  int N;
  Node<T>* Head;
  Node<T>* Tail;
  Queue();
  ~Queue();
  bool push(T x);
  T pop();
  T front();    
  int size();
  bool empty();
};
template<typename T> Queue<T>::Queue() {
  Head = Tail = 0, N = 0;    
}
template<typename T> Queue<T>::~Queue() {
  Node<T>* ptr;
  while(Head) {
    ptr = Head;
    Head = ptr->Next;
    Node<T>::DesmontaNode(ptr);
  }    
}
template<typename T> bool Queue<T>::push(T x) {
  Node<T>* ptr = Node<T>::MontaNode(x);
  if(ptr == nullptr) return 0;
  if(Head) Tail->Next = ptr;
  else Head = ptr;
  Tail = ptr;
  Tail->Next = nullptr;
  N++;
  return 1;
}
template<typename T> T Queue<T>::pop() {
  T x;
  if(Head) {
    Node<T>* ptr = Head;
    Head = Head->Next;
    x = Node<T>::DesmontaNode(ptr);
    if(!Head) Tail = Head;
    N--;
  }
  return x;
}
template<typename T> int Queue<T>::size() {
  return N;
}
template<typename T> bool Queue<T>::empty() {
  return !N;
}
template<typename T> T Queue<T>::front() {
  T x;
  if(Head) x = Head->D;
  return x;
}
// }}}

int main() {
  // azul, vermelho, roxo, branco
  string primeiro[13], segundo[13], terceiro[13], quarto[13];
  for(int i = 0, a = 0, b = 0, c = 0, d = 0; i < 52; i++) {
    string str; cin >> str;
    if(str[0] == '1') primeiro[a++] = str;
    else if(str[0]=='2') segundo[b++] = str;
    else if(str[0]=='3') terceiro[c++] = str;
    else quarto[d++] = str;
  }
  string ordem = "AVRB";
  Queue<Ficha> jogadores[4];
  for(int l = 0; l < 4; l++) {
    int k = -1;
    for(int i = 0; i < 13; i++) {
      if(primeiro[i][1] == ordem[l]) k = 0;
      else if(segundo[i][1] == ordem[l]) k = 1;
      else if(terceiro[i][1] == ordem[l]) k = 2;
      else if(quarto[i][1] == ordem[l]) k = 3;
    }
    if(k == 0) {
      for(int j = 0; j < 13; j++) {
        jogadores[l].push(Ficha(primeiro[j][0], primeiro[j][1], primeiro[j][2]));
      }
    } else if(k == 1) {
      for(int j = 0; j < 13; j++) {
        jogadores[l].push(Ficha(segundo[j][0], segundo[j][1], segundo[j][2]));
      }
    } else if(k == 2) {
      for(int j = 0; j < 13; j++) {
        jogadores[l].push(Ficha(terceiro[j][0], terceiro[j][1], terceiro[j][2]));
      }
    } else {
      for(int j = 0; j < 13; j++) {
        jogadores[l].push(Ficha(quarto[j][0], quarto[j][1], quarto[j][2]));
      }
    }
  }
  int size = 0;
  char matrix[6][6];
  Stack<char> tabuleiro[6];
  memset(matrix, '0', sizeof(matrix));
  int towersIndex[6] = {5, 5, 5, 5, 5, 5};
  while(size < 36) {
    cout << "size: " << size << '\n';
    for(int i = 0; i < 4; i++) {
      char save = '0';
      int torre = jogadores[i].front().tower - 49;
      int saveTower = torre;
      while(tabuleiro[torre].size() == 6) torre = (torre + 1) % 6;
      if(jogadores[i].front().color == 'P') {
        if(tabuleiro[saveTower].size() > 0) {
          tabuleiro[saveTower].pop();
          size--;
          matrix[++towersIndex[saveTower]][saveTower] = save;
        }
      } else {
        tabuleiro[torre].push(jogadores[i].front().color);
        save = jogadores[i].front().color;
        size++;
        matrix[towersIndex[torre]--][torre] = save;
      }
      jogadores[i].pop();
      cout << "Tabuleiro atual:" << '\n';
      for(int j = 0; j < 6; j++) {
        for(int k = 0; k < 6; k++) {
          cout << matrix[j][k] << ' ';
        }
        cout << '\n';
      }
      cout << '\n';
    }
  }
  int resultados[4];
  memset(resultados, 0, sizeof(resultados));
  for(int i = 0; i < 6; i++) {
    if(matrix[i][i] == 'A') resultados[0]++;
    else if(matrix[i][i] == 'V') resultados[1]++;
    else if(matrix[i][i] == 'R') resultados[2]++;
    else resultados[3]++; 
  }
  int maior = *max_element(resultados, resultados + 4);
  bool primeiroesp = 1;
  cout << "Vencedores:" << '\n';
  for(int i = 0; i < 4; i++) {
    if(resultados[i] == maior) {
      if(primeiroesp == 0) cout << ' ';
      cout << ordem[i];
      primeiroesp = 0;
    }
  }
  cout << '\n' << '\n';
  for(int i = 0; i < 4; i++) {
    cout << "Mao do jogador " << i + 1 << ": ";
    if(jogadores[i].empty() == 1) cout << "Vazia" << '\n';
    else {
      bool segundoesp = 1;
      while(!jogadores[i].empty()) {
        if(segundoesp == 0) cout << ' ';
        cout << jogadores[i].front().player << jogadores[i].front().color << jogadores[i].front().tower;
        jogadores[i].pop();
        segundoesp = 0;
      }
      cout << '\n';
    }
  }
  cout << '\n';
  cout << "Tabuleiro final:" << '\n';
  for(int i = 0; i < 6; i++) {
    for(int j = 0; j < 6; j++) {
      cout << matrix[i][j];
      if(j < 5) cout << ' ';
    }
    cout << '\n';
  }
  cout << '\n';
}
