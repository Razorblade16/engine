#include "TestScene.h"
#include "AssetManaging/Texture2D.h"

#ifdef _WIN32
#include "libs/OpenGL/GLEW/include/GL/glew.h"
#else
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

#define INPUT_MANAGER (InputManager::GetSingleton())
#define LOGGER (Logger::GetSingleton())

namespace star
{
	TestScene::TestScene(const tstring & Name):
		BaseScene(Name),
		m_TotalFrames(0),
		m_FPS(0),
		m_PassedMiliseconds(0),
		m_pObjectOne(nullptr),
		m_pObjectTwo(nullptr),
		m_pRectCompOne(nullptr),
		m_pRectCompTwo(nullptr),
		m_pColMan(nullptr)
	{
		
	}

	status TestScene::Initialize( const Context& contex )
	{
		m_pObjectOne = new Object();
		m_pRectCompOne = new RectangleColliderComponent(10,10);
		m_pObjectOne->AddComponent(m_pRectCompOne);
		m_pObjectOne->GetComponent<TransformComponent>()->Scale(2,2,1);

		m_pObjectTwo = new Object();
		m_pRectCompTwo = new CircleColliderComponent(10);
		m_pObjectTwo->AddComponent(m_pRectCompTwo);
		m_pObjectTwo->GetComponent<TransformComponent>()->Translate(19,0,0);
		

		m_pColMan = new CollisionManager();
		m_pColMan->AddObject(m_pObjectOne);
		m_pColMan->AddObject(m_pObjectTwo);

		m_pColMan->CheckCollision(_T("Default"));

		m_Initialized=true;

		star::TextureManager::GetInstance()->LoadTexture(_T("TestDaPng.png"),_T("TestPNG"));
		star::TextureManager::GetInstance()->LoadTexture(_T("Awesome.png"),_T("Awesome"));

		//LOGGER->Log(star::LogLevel::Info,_T("Started making shader"));
		//if(!mTextureShader.Init(_T("jni/Shaders/BaseTexShader.vert"),_T("jni/Shaders/BaseTexShader.frag")))
		//{
		//	LOGGER->Log(star::LogLevel::Info,_T("Making Shader Failed"));
		//}
		//LOGGER->Log(star::LogLevel::Info,_T("Stopped making shader"));
		return STATUS_OK;
	}

	status TestScene::Update(const Context& context)
	{
		++m_TotalFrames;
		m_PassedMiliseconds += float(context.mTimeManager->GetMicroSeconds());
		if(m_PassedMiliseconds >= 1000000)
		{
			m_FPS = m_TotalFrames;
			m_TotalFrames = 0;
			m_PassedMiliseconds -= 1000000;

			tstringstream str;
			str << "FPS: " << m_FPS;

			LOGGER->Log(LogLevel::Info, str.str());
		}

		return STATUS_OK;
	}

	status TestScene::Draw()
	{
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f); // Clear the background of our window to red

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); //Clear the colour buffer (more buffers later on)

#ifdef _WIN32

		glEnable(GL_TEXTURE_2D);
		
		glBindTexture(GL_TEXTURE_2D, star::TextureManager::GetInstance()->GetTextureID(_T("TestPNG")));

		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(-8.0f, -8.0f);
		glTexCoord2f(1.0, 0.0); glVertex2f(0.0f, -8.0f);
		glTexCoord2f(1.0, 1.0); glVertex2f(0.0f, 0.0f);
		glTexCoord2f(0.0, 1.0); glVertex2f(-8.0f, 0.0f);
		glEnd();

		
		glBindTexture(GL_TEXTURE_2D, star::TextureManager::GetInstance()->GetTextureID(_T("Awesome")));
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(0.0f, 0.0f);
		glTexCoord2f(1.0, 0.0); glVertex2f(8.0f, 0.0f);
		glTexCoord2f(1.0, 1.0); glVertex2f(8.0f, 8.0f);
		glTexCoord2f(0.0, 1.0); glVertex2f(0.0f, 8.0f);
		glEnd();

		glDisable(GL_TEXTURE_2D);

#else
		/*
		mTextureShader.Bind();
		glEnable(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, star::TextureManager::GetInstance()->GetTextureID(_T("TestPNG")));

		static const GLfloat squareVertices[] = {
		        -1.0f, -1.0f,
		        1.0f, -1.0f,
		        -1.0f,  1.0f,
		        1.0f,  1.0f,
		    };

		static const GLfloat textureVertices[] = {
		        1.0f, 1.0f,
		        1.0f, 0.0f,
		        0.0f,  1.0f,
		        0.0f,  0.0f,
		};
		const GLfloat gTriangleVertices[] = { 0.0f, 0.5f, -0.5f, -0.5f,
		        0.5f, -0.5f };
		glVertexAttribPointer(0, 2, GL_FLOAT,GL_FALSE,0, gTriangleVertices);
		glEnableVertexAttribArray(0);
		//glVertexAttribPointer(ATTRIB_TEXTUREPOSITON, 2, GL_FLOAT, 0, 0, textureVertices);
		//glEnableVertexAttribArray(ATTRIB_TEXTUREPOSITON);
		glDrawArrays(GL_TRIANGLES,0,3);
		mTextureShader.Unbind();�
		*/
#endif

		return STATUS_OK;
	}



}