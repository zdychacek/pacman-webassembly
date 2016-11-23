#include "SoundManager.h"

SoundManager *SoundManager::s_pInstance = nullptr;

SoundManager::SoundManager()
{
	m_bSounds = true;

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
  {
    std::cerr << "Could not initilize SDL_mixer! Error: " << SDL_GetError();
		m_bSounds = false;
  }
}

SoundManager::~SoundManager()
{
  Mix_CloseAudio();
}

bool SoundManager::load(std::string fileName, std::string id, sound_type type)
{
  if (type == SOUND_MUSIC)
  {
    Mix_Music *pMusic = Mix_LoadMUS(fileName.c_str());

    if (pMusic == nullptr)
    {
      std::cout << "Could not load music: ERROR - " << Mix_GetError() << std::endl;
      return false;
    }

    m_music[id] = pMusic;
    return true;
  }
  else if (type == SOUND_SFX)
  {
    Mix_Chunk *pChunk = Mix_LoadWAV(fileName.c_str());

    if (pChunk == nullptr)
    {
      std::cout << "Could not load SFX: ERROR - " << Mix_GetError() << std::endl;
      return false;
    }

    m_sfxs[id] = pChunk;
    return true;
  }
  return false;
}

void SoundManager::playMusic(std::string id, int loop)
{
  Mix_PlayMusic(m_music[id], loop);
}

void SoundManager::playSound(std::string id, int loop)
{
  Mix_PlayChannel(-1, m_sfxs[id], loop);
}
