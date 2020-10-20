
#include <iostream>
#include <memory>
#include <cmath>
#include <algorithm>

#include <SDL2/SDL.h>

constexpr double Pi = acos(-1.);

#ifdef _WIN32
# include <SDL2/SDL_main.h>
#endif

constexpr int WIDTH = 1000, HEIGHT = 1000;

int main(int, char**)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	auto win = std::shared_ptr<SDL_Window>(
			SDL_CreateWindow(
						"Мое окошко",
						SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
						WIDTH, HEIGHT,
						SDL_WINDOW_SHOWN),
			SDL_DestroyWindow);
	if (win == nullptr) {
		std::cerr << "Ошибочка при создании окна" <<
				SDL_GetError() << std::endl;
		return 1;
	}

	auto ren = std::shared_ptr<SDL_Renderer>(
			SDL_CreateRenderer(win.get(), -1,
					SDL_RENDERER_ACCELERATED |
					SDL_RENDERER_PRESENTVSYNC),
			SDL_DestroyRenderer);
	if (ren == nullptr) {
		std::cerr << "Ошибочка при создании рендера: " <<
				SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Event event;

	for (;;) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) return 0;
		}

		SDL_SetRenderDrawColor(ren.get(), 20, 20, 20, 255);
		SDL_RenderClear(ren.get());

		SDL_SetRenderDrawColor(ren.get(), 166,116,79,255);
		SDL_Rect walls = {200, 300, 600, 600};
		SDL_RenderFillRect(ren.get(), &walls);

		SDL_SetRenderDrawColor(ren.get(), 50,50,50,255);
		SDL_Rect truba = {650, 100, 60, 200};
		SDL_RenderFillRect(ren.get(), &truba);

		SDL_SetRenderDrawColor(ren.get(), 93, 44 ,114, 255); //крыша
		int i;
		int j;
		int k = 0;
		for (i = 600; i > 0; i=i-2){
			j = 600 - i;
			k ++;
			SDL_RenderDrawLine(ren.get(), 200+j/2,300-k,800-j/2,300-k);
		}

		SDL_SetRenderDrawColor(ren.get(), 190,255,199,255);
		SDL_Rect window = {300, 500, 200, 200};
		SDL_RenderFillRect(ren.get(), &window);

		SDL_SetRenderDrawColor(ren.get(), 90,70,50,255);
		SDL_Rect door = {550, 500, 200, 400};
		SDL_RenderFillRect(ren.get(), &door);

		SDL_SetRenderDrawColor(ren.get(), 255,255,255,255); //sinc
		double w;
		for(i = 0; i<=WIDTH; i++){
			double tempy = ((sin(i*0.1-50)/(i*0.1-50))*100+500)*(-1)+1000;
			if (i*0.1-50 == 0){
				tempy = 400;
			}
			if (i>0){
				SDL_RenderDrawLine(ren.get(),i-1, w, i, tempy);
			}
			SDL_RenderDrawPoint(ren.get(), i, tempy);
			w = tempy;
		}

		/*SDL_SetRenderDrawColor(ren.get(), 255,255,255,255); //круг по точкам
		for (double i = 0; i<6.28; i=i+0.01){
			SDL_RenderDrawPoint(ren.get(),cos(i)*300+500,sin(i)*300+500);
		}*/


		int X1 = 500; //круг Брезенхэма
		int Y1 = 500;
		int x = 0;
		int y = 200;
		int error = 0;
		int delta = 1 - 2 * y;
		SDL_SetRenderDrawColor(ren.get(), 255,255,255,255);
		while (y >= 0){
			SDL_RenderDrawPoint(ren.get(),X1 + x, Y1 + y);
			SDL_RenderDrawPoint(ren.get(),X1 + x, Y1 - y);
			SDL_RenderDrawPoint(ren.get(),X1 - x, Y1 + y);
			SDL_RenderDrawPoint(ren.get(),X1 - x, Y1 - y);
		    error = 2 * (delta + y) - 1;
		    if ((delta < 0) && (error <= 0)){
		        delta += 2 * ++x + 1;
		        continue;
		    }
		    if ((delta > 0) && (error > 0)){
		        delta -= 2 * --y + 1;
		        continue;
		    }
		    delta += 2 * (++x - --y);
		}



		SDL_RenderPresent(ren.get());
	}


	return 0;
}

