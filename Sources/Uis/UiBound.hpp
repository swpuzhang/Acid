#pragma once

#include <map>
#include "Maths/Vector2.hpp"

namespace acid
{
	/// <summary>
	/// A rectangle made of a position and dimension.
	/// </summary>
	class ACID_EXPORT UiBound
	{
	public:
		Vector2 m_position;
		Vector2 m_reference;
		bool m_aspectPosition;
		bool m_aspectSize;
		Vector2 m_dimensions;

		/// <summary>
		/// Constructor for rectangle.
		/// </summary>
		/// <param name="position"> The object screen position. </param>
		/// <param name="reference"> The reference pivot vertex (TopLeft, TopCentre, TopRight, CentreLeft, Centre, CentreRight, BottomLeft, BottomCentre, BottomRight). </param>
		/// <param name="aspectPosition"> The if the x position will change with display width. </param>
		/// <param name="aspectSize"> The if the width will scale with display width. </param>
		/// <param name="dimensions"> The object dimensions. </param>
		explicit UiBound(const Vector2 &position, const std::string &reference = "TopLeft", const bool &aspectPosition = true, const bool &aspectSize = true, const Vector2 &dimensions = Vector2(1.0f, 1.0f));

		static Vector2 FindPivot(const std::string &key);

		Vector2 GetPosition() const { return m_position; }

		void SetPosition(const Vector2 &position) { m_position = position; }

		Vector2 GetReference() const { return m_reference; }

		void SetReference(const Vector2 &reference) { m_reference = reference; }

		bool IsAspectPosition() const { return m_aspectPosition; }

		void SetAspectPosition(const bool &aspectPosition) { m_aspectPosition = aspectPosition; }

		bool IsAspectSize() const { return m_aspectSize; }

		void SetAspectSize(const bool &aspectSize) { m_aspectSize = aspectSize; }

		Vector2 GetDimensions() const { return m_dimensions; }

		void SetDimensions(const Vector2 &dimensions) { m_dimensions = dimensions; }

		bool operator==(const UiBound &other) const;

		bool operator!=(const UiBound &other) const;
	};
}
