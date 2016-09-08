// SphereWorld.cpp
// OpenGL SuperBible
// New and improved (performance) sphere world
// Program by Richard S. Wright Jr.
#include"SolarSystem4.h"

bool LoadBMPTexture(const char *szFileName, GLenum minFilter, GLenum magFilter, GLenum wrapMode)	
{
	GLbyte *pBits;
	GLint iWidth, iHeight;

	pBits = gltReadBMPBits(szFileName, &iWidth, &iHeight);
	if(pBits == NULL)
		return false;

	// Set Wrap modes
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);

	// Do I need to generate mipmaps?
	if(minFilter == GL_LINEAR_MIPMAP_LINEAR || minFilter == GL_LINEAR_MIPMAP_NEAREST || minFilter == GL_NEAREST_MIPMAP_LINEAR || minFilter == GL_NEAREST_MIPMAP_NEAREST)
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, iWidth, iHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, pBits);
	return true;
}
GLfloat Findangle(GLfloat a,GLfloat b,GLfloat e,GLfloat s)
{
	GLfloat top=PI,bottom=0.0f;
	GLfloat angle=(top+bottom)/2;
	GLfloat tmps;
	while(abs(top-bottom)>PRECISION)
	{
		tmps=0.5f*a*b*(angle-e*sin(angle));
		if(tmps<s)
			bottom=angle;
		else if(tmps>s)
			top=angle;
		else
			return angle;
		angle=(top+bottom)/2;
	}
	return angle;
}

void Track(GLfloat a,GLfloat b,int pins,GLBatch * lineLoopBatch)
{
	for(int i=0;i<pins;i++)
	{
		vPoints[i][0]=a*cos((GLfloat)i*2*PI/pins);
		vPoints[i][1] = 0;
		vPoints[i][2] = b*sin((GLfloat)i*2*PI/pins);
	}
	lineLoopBatch->Begin(GL_LINE_LOOP,pins);
    lineLoopBatch->CopyVertexData3f(vPoints);
    lineLoopBatch->End();
}


//////////////////////////////////////////////////////////////////
// This function does any needed initialization on the rendering
// context. 
void SetupRC()
    {
	// Initialze Shader Manager
	shaderManager.InitializeStockShaders();
	
	glEnable(GL_DEPTH_TEST);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	// This makes a torus
	gltMakeSphere(sunBatch, 0.5f, 26, 13);
	gltMakeSphere(waterBatch,0.1f,26,13);
	gltMakeSphere(jinBatch,0.15f,26,13);
	gltMakeSphere(earthBatch,0.3f,26,13);
	gltMakeSphere(moonBatch,0.1f,26,13);
	gltMakeSphere(huoBatch,0.2f,26,13);
	gltMakeSphere(muBatch,0.2f,26,13);
	gltMakeSphere(tuBatch,0.2f,26,13);
	gltMakeSphere(twBatch,0.2f,26,13);
	gltMakeSphere(hwBatch,0.2f,26,13);
	gltMakeSphere(sphereBatch, 0.1f, 26, 13);
	//gltMakeSphere(sunBatch, SUNR, 26, 13);
	//gltMakeSphere(waterBatch,WATERR,26,13);
	//gltMakeSphere(jinBatch,JINR,26,13);
	//gltMakeSphere(earthBatch,EARTHR,26,13);
	//gltMakeSphere(moonBatch,0.1f,26,13);
	//gltMakeSphere(huoBatch,HUOR,26,13);
	//gltMakeSphere(muBatch,MUR,26,13);
	//gltMakeSphere(tuBatch,TUR,26,13);
	//gltMakeSphere(twBatch,TWR,26,13);
	//gltMakeSphere(hwBatch,HWR,26,13);
	//gltMakeSphere(mwBatch,0.2f,26,13);
	
	GLfloat vVerts[] = { 0.0f, 5.0f, 0.0f, 
		                  0.0f, -5.0f, 0.0f};
	pointBatch.Begin(GL_POINTS,2);
	pointBatch.CopyVertexData3f(vVerts);
	pointBatch.End();

	glGenTextures(10, uiTextures);
	glBindTexture(GL_TEXTURE_2D, uiTextures[0]);
	//LoadTGATexture("sun.tga", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);
	LoadBMPTexture("太阳.bmp", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, uiTextures[1]);
	LoadBMPTexture("水星.bmp", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);
	//LoadTGATexture("earth.tga", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, uiTextures[2]);
	LoadBMPTexture("金星.bmp", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);
	//LoadTGATexture("moon.tga", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);
	//Track();
	glBindTexture(GL_TEXTURE_2D, uiTextures[3]);
	LoadBMPTexture("地球.bmp", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, uiTextures[4]);
	LoadBMPTexture("月球.bmp", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, uiTextures[5]);
	LoadBMPTexture("火星.bmp", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, uiTextures[6]);
	LoadBMPTexture("木星.bmp", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, uiTextures[7]);
	LoadBMPTexture("土星.bmp", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, uiTextures[8]);
	LoadBMPTexture("天王星.bmp", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, uiTextures[9]);
	LoadBMPTexture("海王星.bmp", GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);
}


///////////////////////////////////////////////////
// Screen changes size or is initialized
void ChangeSize(int nWidth, int nHeight)
{
	glViewport(0, 0, nWidth, nHeight);
	
    // Create the projection matrix, and load it on the projection matrix stack
	viewFrustum.SetPerspective(45.0f, float(nWidth)/float(nHeight), 1.0f, 100000.0f);
	projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
    
    // Set the transformation pipeline to use the two matrix stacks 
	transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
}

        
// Called to draw scene
void RenderScene(void)
{
    // Color values
    static GLfloat vSunColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	static GLfloat vEarthColor[]={0.0f,1.0f,0.0f,1.0f};
	static GLfloat vMoonColor[]={0.0f,0.0f,1.0f,1.0f};
	static GLfloat vWaterColor[]={0.3f,0.6f,0.5f,1.0f};
	static GLfloat vWhite[]={1.0f,1.0f,1.0f,1.0f};
	static GLfloat vLightPos[] = { EARTHA*EARTHL, 0.0f, 0.0f, 1.0f };//光源位置

    // Time Based animation
	static CStopWatch	rotTimer;
	float yRot = rotTimer.GetElapsedSeconds()*10.0f;
	yRot = fmod(yRot,NS);
	
	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//	GLfloat vRed[]={1.0f, 0.0f, 0.0f, 1.0f};
	//shaderManager.UseStockShader(GLT_SHADER_IDENTITY,vRed);
	//pointBatch.Draw();
    // Save the current modelview matrix (the identity matrix)
	modelViewMatrix.PushMatrix();
	// Get the light position in eye space
	M3DVector4f	vLightTransformed;
	M3DMatrix44f mCamera;
    cameraFrame.GetCameraMatrix(mCamera);
    modelViewMatrix.PushMatrix(mCamera);	

	m3dTransformVector4(vLightTransformed, vLightPos, mCamera);

    // 向下移-1.0f是为了看见轨迹线
    modelViewMatrix.Translate(0.0f, -1.0f, -10.0f);

	//地球
	modelViewMatrix.PushMatrix();
	//画地球运动的轨迹
	GLfloat earths=PI*EARTHA*EARTHB;
	bool earthflag=false;
	if(yRot>(NS/2))
	{
		yRot=NS-yRot;
		earthflag=true;
	}
	modelViewMatrix.Rotate(EARTHGA, 0.0f, 0.0f, 1.0f);
	GLfloat earthRadangle=Findangle(EARTHA,EARTHB,EARTHL,yRot*earths/NS);
	GLfloat earthDegangle=m3dRadToDeg(earthRadangle);
	Track(EARTHA,EARTHB,N,&earthlineLoopBatch);
	shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vEarthColor);
    earthlineLoopBatch.Draw();
	
	//地球绕太阳公转
	
	if(earthflag)
		earthDegangle = 2*PI-earthDegangle;
	modelViewMatrix.Rotate(earthDegangle, 0.0f, 1.0f, 0.0f);
	earthRadangle = m3dDegToRad(earthDegangle);
	GLfloat earthr=sqrt(EARTHA*cos(earthRadangle)*EARTHA*cos(earthRadangle)+EARTHB*sin(earthRadangle)*EARTHB*sin(earthRadangle));
	modelViewMatrix.Translate(earthr, 0.0f, 0.0f);

	//地球自转
	modelViewMatrix.Rotate(-EARTHGA, 0.0f, 0.0f, 1.0f);
	modelViewMatrix.Rotate(-EARTHCA, 0.0f, 0.0f, 1.0f);
	modelViewMatrix.Rotate(earthDegangle*EARTHGT, 0.0f, 1.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, uiTextures[3]);
	//shaderManager.UseStockShader(GLT_SHADER_TEXTURE_POINT_LIGHT_DIFF,
 //                                    modelViewMatrix.GetMatrix(),
 //                                    transformPipeline.GetProjectionMatrix(),
 //                                    vLightTransformed, 
 //                                    vWhite,
 //                                    0);
						  
	shaderManager.UseStockShader(GLT_SHADER_TEXTURE_MODULATE,
								 transformPipeline.GetModelViewProjectionMatrix(),
								 vWhite,
								 0);
    earthBatch.Draw();
	modelViewMatrix.PopMatrix();

	//太阳
	modelViewMatrix.PushMatrix();
	modelViewMatrix.Translate(EARTHA*EARTHL, 0.0f, 0.0f);//移到地球轨道的焦点
	modelViewMatrix.Rotate(-SUNCA, 0.0f, 0.0f, 1.0f);//太阳自转的旋转轴

    modelViewMatrix.Rotate(earthDegangle*EARTHGT/SUNZT, 0.0f, 1.0f, 0.0f);//自转
	glBindTexture(GL_TEXTURE_2D, uiTextures[0]);
	shaderManager.UseStockShader(GLT_SHADER_TEXTURE_MODULATE,
								 transformPipeline.GetModelViewProjectionMatrix(),
								 vWhite,
								 0);
	sunBatch.Draw();
	modelViewMatrix.PopMatrix();

	//水星
	modelViewMatrix.PushMatrix();
	modelViewMatrix.Translate(EARTHA*EARTHL-WATERA*WATERL,0.0f,0.0f);//让水星的焦点移到与地球相对应的位置
	//画水星运动的轨迹
	modelViewMatrix.Rotate(WATERGA, 0.0f, 0.0f, 1.0f);//调整水星公转轨道
	
	Track(WATERA,WATERB,N,&waterlineLoopBatch);
	shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vWaterColor);
    waterlineLoopBatch.Draw();
	
	//水星绕太阳公转
	modelViewMatrix.Rotate(fmod(earthDegangle*EARTHGT/WATERGT,360.0f), 0.0f, 1.0f, 0.0f);//根据地球公转角度算出水星公转角度
	//算出水星对于原点的偏移量
	GLfloat waterr=sqrt(WATERA*cos(earthRadangle*EARTHGT/WATERGT)*WATERA*cos(earthRadangle*365/WATERGT)+WATERB*sin(earthRadangle*365/WATERGT)*WATERB*sin(earthRadangle*365/WATERGT));
	modelViewMatrix.Translate(waterr, 0.0f, 0.0f);

	//水星自转
	modelViewMatrix.Rotate(-WATERGA, 0.0f, 0.0f, 1.0f);//让坐标回到水星轨道旋转之前
	modelViewMatrix.Rotate(-WATERCA, 0.0f, 0.0f, 1.0f);//调整水星的自转轴
	modelViewMatrix.Rotate(fmod(earthDegangle*EARTHGT/WATERZT,360.0f), 0.0f, 1.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, uiTextures[1]);
	shaderManager.UseStockShader(GLT_SHADER_TEXTURE_MODULATE,
								 transformPipeline.GetModelViewProjectionMatrix(),
								 vWhite,
								 0);
    waterBatch.Draw();
	modelViewMatrix.PopMatrix();


	//金星
	modelViewMatrix.PushMatrix();
	modelViewMatrix.Translate(EARTHA*EARTHL-JINA*JINL,0.0f,0.0f);
	//画金星运动的轨迹
	modelViewMatrix.Rotate(JINGA, 0.0f, 0.0f, 1.0f);
	Track(JINA,JINB,N,&jinlineLoopBatch);
	shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vWhite);
    jinlineLoopBatch.Draw();
	
	//金星绕太阳公转

	modelViewMatrix.Rotate(fmod(earthDegangle*EARTHGT/JINGT,360.0f), 0.0f, 1.0f, 0.0f);
	GLfloat jinr=sqrt(JINA*cos(earthRadangle*365/JINGT)*JINA*cos(earthRadangle*365/JINGT)+JINB*sin(earthRadangle*365/JINGT)*JINB*sin(earthRadangle*365/JINGT));
	modelViewMatrix.Translate(jinr, 0.0f, 0.0f);

	//金星自转
	modelViewMatrix.Rotate(-JINGA, 0.0f, 0.0f, 1.0f);
	modelViewMatrix.Rotate(-JINCA, 0.0f, 0.0f, 1.0f);
	modelViewMatrix.Rotate(fmod(earthDegangle*365/JINZT,360.0f), 0.0f, 1.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, uiTextures[2]);
	shaderManager.UseStockShader(GLT_SHADER_TEXTURE_MODULATE,
								 transformPipeline.GetModelViewProjectionMatrix(),
								 vWhite,
								 0);
    jinBatch.Draw();
	modelViewMatrix.PopMatrix();

	//火星
	modelViewMatrix.PushMatrix();
	modelViewMatrix.Translate(EARTHA*EARTHL-HUOA*HUOL,0.0f,0.0f);
	//画火星运动的轨迹
	modelViewMatrix.Rotate(HUOGA, 0.0f, 0.0f, 1.0f);
	Track(HUOA,HUOB,N,&huolineLoopBatch);
	shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vWhite);
    huolineLoopBatch.Draw();
	
	//火星绕太阳公转
	modelViewMatrix.Rotate(fmod(earthDegangle*EARTHGT/HUOGT,360.0f), 0.0f, 1.0f, 0.0f);
	GLfloat huor=sqrt(HUOA*cos(earthRadangle*365/HUOGT)*HUOA*cos(earthRadangle*365/HUOGT)+HUOB*sin(earthRadangle*365/HUOGT)*HUOB*sin(earthRadangle*365/HUOGT));
	modelViewMatrix.Translate(huor, 0.0f, 0.0f);

	//火星自转
	modelViewMatrix.Rotate(-HUOGA, 0.0f, 0.0f, 1.0f);
	modelViewMatrix.Rotate(-HUOCA, 0.0f, 0.0f, 1.0f);
	modelViewMatrix.Rotate(fmod(earthDegangle*365/HUOZT,360.0f), 0.0f, 1.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, uiTextures[5]);
	shaderManager.UseStockShader(GLT_SHADER_TEXTURE_MODULATE,
								 transformPipeline.GetModelViewProjectionMatrix(),
								 vWhite,
								 0);
    huoBatch.Draw();
	modelViewMatrix.PopMatrix();
	

	//木星
	modelViewMatrix.PushMatrix();
	modelViewMatrix.Translate(EARTHA*EARTHL-MUA*MUL,0.0f,0.0f);
	//画木星运动的轨迹
	modelViewMatrix.Rotate(MUGA, 0.0f, 0.0f, 1.0f);
	Track(MUA,MUB,N,&mulineLoopBatch);
	shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vWhite);
    mulineLoopBatch.Draw();
	
	//木星绕太阳公转
	modelViewMatrix.Rotate(fmod(earthDegangle*EARTHGT/MUGT,360.0f), 0.0f, 1.0f, 0.0f);
	GLfloat mur=sqrt(MUA*cos(earthRadangle*365/MUGT)*MUA*cos(earthRadangle*365/MUGT)+MUB*sin(earthRadangle*365/MUGT)*MUB*sin(earthRadangle*365/MUGT));
	modelViewMatrix.Translate(mur, 0.0f, 0.0f);

	//木星自转
	modelViewMatrix.Rotate(-MUGA, 0.0f, 0.0f, 1.0f);
	modelViewMatrix.Rotate(-MUCA, 0.0f, 0.0f, 1.0f);
	modelViewMatrix.Rotate(fmod(earthDegangle*365/MUZT,360.0f), 0.0f, 1.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, uiTextures[6]);
	shaderManager.UseStockShader(GLT_SHADER_TEXTURE_MODULATE,
								 transformPipeline.GetModelViewProjectionMatrix(),
								 vWhite,
								 0);
    muBatch.Draw();
	modelViewMatrix.PopMatrix();


	//土星
	modelViewMatrix.PushMatrix();
	modelViewMatrix.Translate(EARTHA*EARTHL-TUA*TUL,0.0f,0.0f);
	//画土星运动的轨迹
	modelViewMatrix.Rotate(TUGA, 0.0f, 0.0f, 1.0f);
	Track(TUA,TUB,N,&tulineLoopBatch);
	shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vWhite);
    tulineLoopBatch.Draw();
	
	//土星绕太阳公转
	modelViewMatrix.Rotate(fmod(earthDegangle*EARTHGT/TUGT,360.0f), 0.0f, 1.0f, 0.0f);
	GLfloat tur=sqrt(TUA*cos(earthRadangle*365/TUGT)*TUA*cos(earthRadangle*365/TUGT)+TUB*sin(earthRadangle*365/TUGT)*TUB*sin(earthRadangle*365/TUGT));
	modelViewMatrix.Translate(tur, 0.0f, 0.0f);

	//土星自转
	modelViewMatrix.Rotate(-TUGA, 0.0f, 0.0f, 1.0f);
	modelViewMatrix.Rotate(-TUCA, 0.0f, 0.0f, 1.0f);
	modelViewMatrix.Rotate(fmod(earthDegangle*365/TUZT,360.0f), 0.0f, 1.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, uiTextures[7]);
	shaderManager.UseStockShader(GLT_SHADER_TEXTURE_MODULATE,
								 transformPipeline.GetModelViewProjectionMatrix(),
								 vWhite,
								 0);
    tuBatch.Draw();
	modelViewMatrix.PopMatrix();
	
	//天王星
	modelViewMatrix.PushMatrix();
	modelViewMatrix.Translate(EARTHA*EARTHL-TWA*TWL,0.0f,0.0f);
	//画天王星运动的轨迹
	modelViewMatrix.Rotate(TWGA, 0.0f, 0.0f, 1.0f);
	Track(TWA,TWB,N,&twlineLoopBatch);
	shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vWhite);
    twlineLoopBatch.Draw();
	
	//天王星绕太阳公转
	modelViewMatrix.Rotate(fmod(earthDegangle*EARTHGT/TWGT,360.0f), 0.0f, 1.0f, 0.0f);
	GLfloat twr=sqrt(TWA*cos(earthRadangle*365/TWGT)*TWA*cos(earthRadangle*365/TWGT)+TWB*sin(earthRadangle*365/TWGT)*TWB*sin(earthRadangle*365/TWGT));
	modelViewMatrix.Translate(twr, 0.0f, 0.0f);

	//天王星自转
	modelViewMatrix.Rotate(-TWGA, 0.0f, 0.0f, 1.0f);
	modelViewMatrix.Rotate(-TWCA, 0.0f, 0.0f, 1.0f);
	modelViewMatrix.Rotate(fmod(earthDegangle*365/TWZT,360.0f), 0.0f, 1.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, uiTextures[8]);
	shaderManager.UseStockShader(GLT_SHADER_TEXTURE_MODULATE,
								 transformPipeline.GetModelViewProjectionMatrix(),
								 vWhite,
								 0);
    twBatch.Draw();
	modelViewMatrix.PopMatrix();

	//海王星
	modelViewMatrix.PushMatrix();
	modelViewMatrix.Translate(EARTHA*EARTHL-HWA*HWL,0.0f,0.0f);
	//画海王星运动的轨迹
	modelViewMatrix.Rotate(HWGA, 0.0f, 0.0f, 1.0f);
	Track(HWA,HWB,N,&hwlineLoopBatch);
	shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vWhite);
    hwlineLoopBatch.Draw();
	
	//海王星绕太阳公转
	modelViewMatrix.Rotate(fmod(earthDegangle*EARTHGT/HWGT,360.0f), 0.0f, 1.0f, 0.0f);
	GLfloat hwr=sqrt(HWA*cos(earthRadangle*365/HWGT)*HWA*cos(earthRadangle*365/HWGT)+HWB*sin(earthRadangle*365/HWGT)*HWB*sin(earthRadangle*365/HWGT));
	modelViewMatrix.Translate(hwr, 0.0f, 0.0f);

	//海王星自转
	modelViewMatrix.Rotate(-HWGA, 0.0f, 0.0f, 1.0f);
	modelViewMatrix.Rotate(-HWCA, 0.0f, 0.0f, 1.0f);
	modelViewMatrix.Rotate(fmod(earthDegangle*365/HWZT,360.0f), 0.0f, 1.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, uiTextures[9]);
	shaderManager.UseStockShader(GLT_SHADER_TEXTURE_MODULATE,
								 transformPipeline.GetModelViewProjectionMatrix(),
								 vWhite,
								 0);
    hwBatch.Draw();
	modelViewMatrix.PopMatrix();


	// Restore the previous modleview matrix (the idenity matrix)
	modelViewMatrix.PopMatrix();
	modelViewMatrix.PopMatrix();
        
    // Do the buffer Swap
    glutSwapBuffers();
    // Tell GLUT to do it again
    glutPostRedisplay();
}

void SpecialKeys(int key, int x, int y)
{
	float linear = 2.0f;
	float angular = float(m3dDegToRad(5.0f));
	
	if(key == GLUT_KEY_UP)
		cameraFrame.MoveUp(linear);

	if(key == GLUT_KEY_DOWN)
		cameraFrame.MoveUp(-linear);
	
	if(key == GLUT_KEY_LEFT)
		cameraFrame.RotateWorld(angular, 0.0f, 1.0f, 0.0f);
	
	if(key == GLUT_KEY_RIGHT)
		cameraFrame.RotateWorld(-angular, 0.0f, 1.0f, 0.0f);		
	
}

void FuncKeys(unsigned char key, int x, int y)
{
	float linear = 2.0f;
	if(key == 'w')
		cameraFrame.MoveForward(linear);
	if(key == 's')
		cameraFrame.MoveForward(-linear);
	if(key == 'a')
		cameraFrame.MoveRight(linear);
	if(key == 'd')
		cameraFrame.MoveRight(-linear);
	if(key == ' ')
		cameraFrame.SetOrigin(0.0f,0.0f,0.0f);
}

void ShutdownRC(void)
{
    glDeleteTextures(1, uiTextures);
}

int main(int argc, char* argv[])
{
	gltSetWorkingDirectory(argv[0]);
		
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,600);
  
    glutCreateWindow("OpenGL Solar System");
 
	glutSpecialFunc(SpecialKeys);
	glutKeyboardFunc(FuncKeys);
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
        return 1;
        }
        

    SetupRC();
    glutMainLoop();
	ShutdownRC();
    return 0;
}
