#include "Camera.h"

Camera::Camera() { updateCamera(); };
Camera::~Camera() {};


glm::mat4 Camera::lookAt(const glm::vec4& eye, const glm::vec4& at, const glm::vec4& up)
{	
	// @TODO: Task1:请按照实验课内容补全相机观察矩阵的计算
	glm::vec3 eye3(eye.x, eye.y, eye.z);
	glm::vec3 at3(at.x, at.y, at.z);
	glm::vec3 up3(up.x, up.y, up.z);
	glm::vec3 f(glm::normalize(at3 - eye3));
	glm::vec3 r(glm::normalize(glm::cross(f, up3)));
	glm::vec3 u(glm::normalize(glm::cross(r, f)));
	glm::mat4 c = glm::mat4(1.0f);
	c[0][0] = r.x;
	c[1][0] = r.y;
	c[2][0] = r.z;
	c[0][1] = u.x;
	c[1][1] = u.y;
	c[2][1] = u.z;
	c[0][2] = -f.x;
	c[1][2] = -f.y;
	c[2][2] = -f.z;
	c[3][0] = -glm::dot(r, eye3);
	c[3][1] = -glm::dot(u, eye3);
	c[3][2] = glm::dot(f, eye3);
	return c;
			
}


glm::mat4 Camera::ortho(const GLfloat left, const GLfloat right,
	const GLfloat bottom, const GLfloat top,
	const GLfloat zNear, const GLfloat zFar)
{
	// @TODO: Task2:请按照实验课内容补全正交投影矩阵的计算
	glm::mat4 c = glm::mat4(1.0f);
	c[0][0] = 2.0f / (right - left);
	c[1][1] = 2.0f / (top - bottom);
	c[2][2] = -2.0f / (zFar - zNear);
	c[3][0] = -(right + left) / (right - left);
	c[3][1] = -(top + bottom) / (top - bottom);
	c[3][2] = -(zFar + zNear) / (zFar - zNear);
	c[3][3] = 1.0f;
	return c;
}


glm::mat4 Camera::perspective(const GLfloat fov, const GLfloat aspect,
	const GLfloat zNear, const GLfloat zFar)
{
	// @TODO: Task3:请按照实验课内容补全透视投影矩阵的计算
	// 计算透视投影矩阵
	glm::mat4 c = glm::mat4(0.0f);

	// 透视投影矩阵的各个参数
	GLfloat top = zNear * tan(glm::radians(fov) / 2.0f);
	GLfloat bottom = -top;
	GLfloat right = top * aspect;
	GLfloat left = -right;

	c[0][0] = (2.0f * zNear) / (right - left);
	c[1][1] = (2.0f * zNear) / (top - bottom);
	c[2][2] = -(zFar + zNear) / (zFar - zNear);
	c[2][3] = -1.0f;
	c[3][2] = -(2.0f * zFar * zNear) / (zFar - zNear);
	return c;
}


glm::mat4 Camera::frustum(const GLfloat left, const GLfloat right,
	const GLfloat bottom, const GLfloat top,
	const GLfloat zNear, const GLfloat zFar)
{
	// 任意视锥体矩阵
	glm::mat4 c = glm::mat4(1.0f);
	c[0][0] = 2.0 * zNear / (right - left);
	c[0][2] = (right + left) / (right - left);
	c[1][1] = 2.0 * zNear / (top - bottom);
	c[1][2] = (top + bottom) / (top - bottom);
	c[2][2] = -(zFar + zNear) / (zFar - zNear);
	c[2][3] = -2.0 * zFar * zNear / (zFar - zNear);
	c[3][2] = -1.0;
	c[3][3] = 0.0;
	c = glm::transpose(c);
	return c;
}


void Camera::updateCamera()
{
	// @TODO: Task1 设置相机位置和方向
	float eyex = 0;			// 根据rotateAngle和upAngle设置x
	float eyey = 0;			// 根据upAngle设置y
	float eyez = radius;	// 根据rotateAngle和upAngle设置z
	
	 eyex = radius * sin(glm::radians(rotateAngle)) * cos(glm::radians(upAngle));
	 eyey = radius * sin(glm::radians(upAngle));
	 eyez = radius * cos(glm::radians(rotateAngle)) * cos(glm::radians(upAngle));
	eye = glm::vec4(eyex, eyey, eyez, 1.0);
	if (upAngle > 90.0)  
		up = glm::vec4(0.0, -1.0, 0.0, 0.0); 
	else 
		up = glm::vec4(0.0, 1.0, 0.0, 0.0); 
	at = glm::vec4(0.0, 0.0, 0.0, 1.0);
	
	// @TODO: Task1:设置相机参数
	// 使用相对于at的角度控制相机的时候，注意在upAngle大于90的时候，相机坐标系的u向量会变成相反的方向，
	// 要将up的y轴改为负方向才不会发生这种问题
	
	
	// 也可以考虑直接控制相机自身的俯仰角，
	// 保存up，eye-at 这些向量，并修改这些向量方向来控制
	// 看到这里的有缘人可以试一试
}


void Camera::keyboard(int key, int action, int mode)
{

	// 键盘事件处理
	if (key == GLFW_KEY_X && action == GLFW_PRESS && mode == 0x0000)
	{
		rotateAngle += 5.0;
	}
	else if(key == GLFW_KEY_X && action == GLFW_PRESS && mode == GLFW_MOD_SHIFT)
	{
		rotateAngle -= 5.0;
	}
	else if(key == GLFW_KEY_Y && action == GLFW_PRESS && mode == 0x0000)
	{
		upAngle += 5.0;
		if (upAngle > 180)
			upAngle = 180;
	}
	else if(key == GLFW_KEY_Y && action == GLFW_PRESS && mode == GLFW_MOD_SHIFT)
	{
		upAngle -= 5.0;
		if (upAngle < -180)
			upAngle = -180;
	}
	else if(key == GLFW_KEY_R && action == GLFW_PRESS && mode == 0x0000)
	{
		radius += 0.1;
	}
	else if(key == GLFW_KEY_R && action == GLFW_PRESS && mode == GLFW_MOD_SHIFT)
	{
		radius -= 0.1;
	}
	else if(key == GLFW_KEY_F && action == GLFW_PRESS && mode == 0x0000)
	{
		fov += 5.0;
	}
	else if(key == GLFW_KEY_F && action == GLFW_PRESS && mode == GLFW_MOD_SHIFT)
	{
		fov -= 5.0;
	}
	else if(key == GLFW_KEY_A && action == GLFW_PRESS && mode == 0x0000)
	{
		aspect += 0.1;
	}
	else if(key == GLFW_KEY_A && action == GLFW_PRESS && mode == GLFW_MOD_SHIFT)
	{
		aspect -= 0.1;
	}
	else if(key == GLFW_KEY_S && action == GLFW_PRESS && mode == 0x0000)
	{
		scale += 0.1;
	}
	else if(key == GLFW_KEY_S && action == GLFW_PRESS && mode == GLFW_MOD_SHIFT)
	{
		scale -= 0.1;
	}
	else if(key == GLFW_KEY_SPACE && action == GLFW_PRESS && mode == 0x0000)
	{
		radius = 4.0;
		rotateAngle = 0.0;
		upAngle = 0.0;
		fov = 45.0;
		aspect = 1.0;
		scale = 1.5;
	}
}
