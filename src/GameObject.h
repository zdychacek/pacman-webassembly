#ifndef __GameObject__
#define __GameObject__

#include <string>
#include <memory>
#include "LoaderParams.h"
#include "Vector2D.h"

class GameObject
{
public:
  // base class needs virtual destructor
  virtual ~GameObject() {}

  // load from file - int x, int y, int width, int height, std::string textureID, int numFrames, int callbackID = 0, int animSpeed = 0
  virtual void load(std::unique_ptr<LoaderParams> const &pParams) = 0;

  // draw the object
  virtual void draw() = 0;

  // do update stuff
  virtual void update() = 0;

  // remove anything that needs to be deleted
  virtual void clean() = 0;

  // getters for common variables
  Vector2D &getPosition() { return m_position; }
  Vector2D &getVelocity() { return m_velocity; }

  int getWidth() { return m_width; }
  int getHeight() { return m_height; }

  // is the object currently being updated?
  bool updating() { return m_bUpdating; }

  // set whether to update the object or not
  void setUpdating(bool updating) { m_bUpdating = updating; }

protected:
  // constructor with default initialisation list
  GameObject() : m_position(0, 0),
		 m_velocity(0, 0),
		 m_acceleration(0, 0),
		 m_width(0),
		 m_height(0),
		 m_currentRow(0),
		 m_currentFrame(0),
		 m_bUpdating(false),
		 m_angle(0),
		 m_alpha(255)
  {
  }

  // movement variables
  Vector2D m_position;
  Vector2D m_velocity;
  Vector2D m_acceleration;

  // size variables
  int m_width;
  int m_height;

  // animation variables
  int m_currentRow;
  int m_currentFrame;
  int m_numFrames;
  std::string m_textureID;

  // common boolean variables
  bool m_bUpdating;

  // rotation
  double m_angle;

  // blending
  int m_alpha;
};

#endif
