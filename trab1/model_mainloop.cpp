#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

#include "oo_model.hpp"

using namespace std::chrono;
uint64_t get_now_ms() {
  return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

int main ()
{
  Corpo *mainplayer = new Corpo(10, 0, 10);

  ListaDeCorpos *l = new ListaDeCorpos();
  l->add_corpo(mainplayer);

  Fisica *f = new Fisica(l);

  Tela *tela = new Tela(l, 40, 40, 40, 40);
  tela->init();

  Teclado *teclado = new Teclado();
  teclado->init();

  uint64_t t0;
  uint64_t t1;
  uint64_t deltaT;
  uint64_t T;

  int i = 0;

  T = get_now_ms();
  t1 = T;
  while (1) {
    // Atualiza timers
    t0 = t1;
    t1 = get_now_ms();
    deltaT = t1-t0;

    // Atualiza modelo
    f->update(deltaT);

    // Atualiza tela
    tela->update();

    // Lê o teclado
    char c = teclado->getchar();
    if (c=='s') {
      f->salto(1);
    }
    if (c=='w')
      f->salto(-1);
    if (c=='q') {
      break;
    }

    // Condicao de parada
    if ( (t1-T) > 1000000 ) break;

    std::this_thread::sleep_for (std::chrono::milliseconds(16));
    i++;
  }
  tela->stop();
  teclado->stop();
  return 0;
}
