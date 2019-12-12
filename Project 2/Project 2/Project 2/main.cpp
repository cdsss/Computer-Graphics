#include<GL/glut.h>

void init(void)
{
	glClearColor(1.0, 1.0, 0.6, 1.0); //设置背景色

	/* 光源 */
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);	// 创建光源
	glEnable(GL_LIGHTING);	// 使光照有效
	glEnable(GL_LIGHT0);	// 使光源0有效

	/* 阴暗处理 */
	glShadeModel(GL_SMOOTH);

	/* 材质 */
	GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 }; // 材质的漫反射光颜色
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

	glEnable(GL_DEPTH_TEST);	// 开启更新深度缓冲区的功能，使视觉效果更真实
}


/* 绘制真实感静态图像 */
void draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//画身体
	glTranslated(0.0f, -0.3f, 0.0f);
	glutSolidSphere(0.5f, 20, 20);

	// 画头
	glTranslated(0.0f, 0.70f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);

	// 画眼睛
	glPushMatrix();
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f, 10, 10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f, 10, 10);
	glPopMatrix();	// 恢复栈顶矩阵状态

	// 画鼻子
	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCone(0.08f, 0.5f, 10, 2);

	glFlush();
}
/* 定义 GLUT 的 reshape 函数，w、h 分别是输出图形的窗口的宽和高*/
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-1.5, 1.5, -1.5 * (GLfloat)h / (GLfloat)w,
			1.5 * (GLfloat)h / (GLfloat)w, -10.0, 10.0); //创建平行视景体
	else
		glOrtho(-1.5 * (GLfloat)w / (GLfloat)h, 1.5 * (GLfloat)
			w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // 显示模式初始化
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);   // 显示窗口
	init();
	glutDisplayFunc(draw);
	glutReshapeFunc(reshape);   // 注册窗口大小改变时的响应函数
	glutMainLoop();
	return 0;
}