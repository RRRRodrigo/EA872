#include <iostream>
#include <chrono>
#include <thread>
#include <vector>


#include "oo_model.hpp"
#include "01-playback.hpp"


using namespace std::chrono;
uint64_t get_now_ms() {
  return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

void espera(uint64_t t0, uint64_t t1){
  while (1) {
    std::this_thread::sleep_for (std::chrono::milliseconds(1));
    t1 = get_now_ms();
    if (t1-t0 > 500) break;
  }
}

int main ()
{
  uint64_t t0, t1;

  Audio::Sample *asample;
  asample = new Audio::Sample();
  asample->load("assets/blip.dat");

  Audio::Player *player;
  player = new Audio::Player();
  player->init();

  while (1) {
    std::this_thread::sleep_for (std::chrono::milliseconds(1));
    t1 = get_now_ms();
    if (t1-t0 > 500) break;
  }

  Corpo *c1 = new Corpo(10, 0, 20);
  Corpo *c2 = new Corpo(10, 0, 19);
  Corpo *c3 = new Corpo(10, 0, 17);
  Corpo *c4 = new Corpo(10, 0, 15);

  ListaDeCorpos *l = new ListaDeCorpos();
  l->add_corpo(c1);
  l->add_corpo(c2);
  l->add_corpo(c3);
  l->add_corpo(c4);

  Fisica *f = new Fisica(l);

  Tela *tela = new Tela(l, 40, 40, 40, 40);
  tela->init();

  Teclado *teclado = new Teclado();
  teclado->init();

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
    if (c=='w') {
	f->choque();
	player->play(asample);
	espera(t0, t1);
	asample->set_position(0);
    }
    if (c=='s') {
	f->choque2();
	player->play(asample);
	espera(t0, t1);
	asample->set_position(0);
    }
    if (c=='q') {
      break;
    }

    // Condicao de parada
    if ( (t1-T) > 1000000 ) break;

    std::this_thread::sleep_for (std::chrono::milliseconds(100));
    i++;
  }
  player->stop();
  tela->stop();
  teclado->stop();
  return 0;
}
