// Nothing to see here ;-)
// Konami + N*de-Raider
#define RETURN \
	return; do { \
		static int ____idx=0; \
		if( \
			   (key == sf::Keyboard::Key::W && ____idx <= 1) \
			|| (key == sf::Keyboard::Key::S && ____idx >= 2 && ____idx <= 3) \
			|| (key == sf::Keyboard::Key::A && (____idx == 4 || ____idx == 6)) \
			|| (key == sf::Keyboard::Key::D && (____idx == 5 || ____idx == 7)) \
			|| (key == sf::Keyboard::Key::B && ____idx == 8) \
		) ++____idx; \
		else {\
			if(key == sf::Keyboard::Key::A && ____idx == 9) \
				killPlayer(true); \
			____idx = 0; \
		}\
    } while(0);
