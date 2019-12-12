#include<GL/glut.h>

void init(void)
{
	glClearColor(1.0, 1.0, 0.6, 1.0); //���ñ���ɫ

	/* ��Դ */
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);	// ������Դ
	glEnable(GL_LIGHTING);	// ʹ������Ч
	glEnable(GL_LIGHT0);	// ʹ��Դ0��Ч

	/* �������� */
	glShadeModel(GL_SMOOTH);

	/* ���� */
	GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 }; // ���ʵ����������ɫ
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

	glEnable(GL_DEPTH_TEST);	// ����������Ȼ������Ĺ��ܣ�ʹ�Ӿ�Ч������ʵ
}


/* ������ʵ�о�̬ͼ�� */
void draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//������
	glTranslated(0.0f, -0.3f, 0.0f);
	glutSolidSphere(0.5f, 20, 20);

	// ��ͷ
	glTranslated(0.0f, 0.70f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);

	// ���۾�
	glPushMatrix();
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f, 10, 10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f, 10, 10);
	glPopMatrix();	// �ָ�ջ������״̬

	// ������
	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCone(0.08f, 0.5f, 10, 2);

	glFlush();
}
/* ���� GLUT �� reshape ������w��h �ֱ������ͼ�εĴ��ڵĿ�͸�*/
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-1.5, 1.5, -1.5 * (GLfloat)h / (GLfloat)w,
			1.5 * (GLfloat)h / (GLfloat)w, -10.0, 10.0); //����ƽ���Ӿ���
	else
		glOrtho(-1.5 * (GLfloat)w / (GLfloat)h, 1.5 * (GLfloat)
			w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // ��ʾģʽ��ʼ��
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);   // ��ʾ����
	init();
	glutDisplayFunc(draw);
	glutReshapeFunc(reshape);   // ע�ᴰ�ڴ�С�ı�ʱ����Ӧ����
	glutMainLoop();
	return 0;
}