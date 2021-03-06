//
// Created by Tobias on 10/2/2020.
//

#ifndef SD3D_ORBITCAMERACONTROLLER_H
#define SD3D_ORBITCAMERACONTROLLER_H

#include <GLFW/glfw3.h>
#include <gsl-lite/gsl-lite.hpp>

#pragma warning(push, 0)

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#pragma warning(pop)

#include "../graphics/Camera.h"

class OrbitCameraController {
public:
	struct OrbitCamSettings {
		glm::vec3 target{};

		float dist{};
		float minDist{};
		float maxDist{};
		float scrollSpeed{};

		float speed{};
		float deceleration{};

		OrbitCamSettings(const glm::vec3 &target, float dist, float speed,
						 float deceleration = 0.05f) :
			OrbitCamSettings{target, dist,  dist,        dist,
							 0.0f,   speed, deceleration} {}

		OrbitCamSettings(const glm::vec3 &target, float dist, float minDist,
						 float maxDist, float scrollSpeed, float speed,
						 float deceleration = 0.05f) :
			target{target},
			dist{dist},
			minDist{minDist},
			maxDist{maxDist},
			scrollSpeed{scrollSpeed},
			speed{speed},
			deceleration{deceleration} {}
	};

private:
	// split mouse vector in 2 directions
	// x -> theta
	// y -> phi

	glm::vec3 m_target{};

	float m_dist{};
	float m_minDist{};
	float m_maxDist{};
	float m_scrollSpeed{};

	float m_yaw{-90.0f};
	float m_pitch{};

	glm::vec2 m_moveVec{};

	float m_deceleration{0.05f};
	float m_speed{};

	Camera m_cam;

	// for settings window
private:
	float m_fovTemp;

	float m_fovSaved;
	OrbitCamSettings m_settingsSaved;

public:
	OrbitCameraController(Camera &&cam, const OrbitCamSettings &settings) :
		m_target{settings.target},
		m_dist{settings.dist},
		m_minDist{settings.minDist},
		m_maxDist{settings.maxDist},
		m_scrollSpeed{settings.scrollSpeed},
		m_deceleration{settings.deceleration},
		m_speed{settings.speed},
		m_cam{cam},
		m_fovTemp{gsl::narrow_cast<float>(m_cam.fov())},
		m_fovSaved{m_fovTemp},
		m_settingsSaved{settings} {}

	void update(float deltaTime);

	[[nodiscard]] const Camera &ccam() const { return m_cam; }
	[[nodiscard]] Camera &cam() { return m_cam; };

	void rotate(double dX, double dY);

	void zoom(double dScroll);

	[[nodiscard]] float min_dist() const { return m_minDist; }

	[[nodiscard]] float max_dist() const { return m_maxDist; }

	void set_min_dist(float val) { m_minDist = val; }

	void set_max_dist(float val) { m_maxDist = val; }

	void settings_gui(bool &show, glm::vec3 &clearCol);

	void reset_settings() {
		m_target = m_settingsSaved.target;
		m_dist = m_settingsSaved.dist;
		m_minDist = m_settingsSaved.minDist;
		m_maxDist = m_settingsSaved.maxDist;
		m_scrollSpeed = m_settingsSaved.scrollSpeed;
		m_deceleration = m_settingsSaved.deceleration;
		m_speed = m_settingsSaved.speed;

		m_fovTemp = m_fovSaved;
		m_cam.set_fov(m_fovTemp);
	}
};

#endif // SD3D_ORBITCAMERACONTROLLER_H
