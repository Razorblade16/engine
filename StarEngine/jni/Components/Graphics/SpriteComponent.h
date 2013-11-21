#pragma once

#include "../../defines.h"
#include "../../Graphics/Shader.h"
#include "../BaseComponent.h"
#include "../../Helpers/Filepath.h"
#include <vector>
#ifdef ANDROID
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <EGL/egl.h>
#endif

namespace star
{
	struct SpriteInfo
	{
		std::vector<GLfloat> vertices;
		std::vector<GLfloat> uvCoords;
		tstring spriteName;
		mat4 transform;
		bool bIsHUD;
	};

	class SpriteComponent : public BaseComponent
	{
	public:
		SpriteComponent(
			const tstring& filepath,
			const tstring& spriteName,
			int32 widthSegments = 1,
			int32 heightSegments = 1
			);

		virtual ~SpriteComponent();

		void Draw();
		virtual void Update(const Context& context);

		virtual bool CheckCulling(
			float left,
			float right,
			float top,
			float bottom
			) const;

		const tstring& GetFilePath() const;
		const tstring& GetName() const;
		virtual int32 GetWidth() const;
		virtual int32 GetHeight() const;
		std::vector<GLfloat> GetVertices() const;
		std::vector<GLfloat> GetUVCoords() const;
		
		void SetCurrentSegment(int32 widthSegment, int32 heightSegment);

		void SetHUDOptionEnabled(bool enabled);
		bool IsHUDOptionEnabled() const;

		void SetTexture(const tstring& filepath, const tstring& spriteName, int32 widthSegments = 1, int32 heightSegments = 1);

	protected:
		virtual void InitializeComponent();
		virtual void CreateVertices();
		virtual void CreateIndices();

		GLfloat m_Vertices[12];
		GLfloat m_UvCoords[8];
		int32 m_Width, m_WidthSegments, m_CurrentWidthSegment;
		int32 m_Heigth, m_HeightSegments, m_CurrentHeightSegment;

	private:
		Filepath m_FilePath;
		tstring m_SpriteName;
		bool m_bIsHudElement;
		
		SpriteInfo m_SpriteInfo;

		SpriteComponent(const SpriteComponent &);
		SpriteComponent(SpriteComponent &&);
		SpriteComponent& operator=(const SpriteComponent &);
		SpriteComponent& operator=(SpriteComponent &&);
	};
}
