#include "JsonSection.hpp"

namespace acid
{
	JsonSection::JsonSection(JsonSection *parent, const std::string &name, const std::string &content) :
		m_parent(parent),
		m_children(std::vector<JsonSection *>()),
		m_name(name),
		m_content(content)
	{
	}

	JsonSection::~JsonSection()
	{
		for (auto &child : m_children)
		{
			delete child;
		}
	}

	void JsonSection::AppendData(const std::shared_ptr<Serialized> &Serialized, std::stringstream &builder, const int &indentation, const bool &end)
	{
		std::stringstream indents;

		for (int i = 0; i < indentation; i++)
		{
			indents << "  ";
		}

		builder << indents.str();

		if (Serialized->GetName().empty())
		{
			builder << "{\n";
		}
		else if (Serialized->GetValue().empty())
		{
			builder << "\"" << Serialized->GetName() << "\": {\n";
		}
		else
		{
			builder << "\"" << Serialized->GetName() + "\": " << Serialized->GetValue();

			if (!end)
			{
				builder << ", ";
			}

			builder << "\n";
		}

		for (auto &child : Serialized->GetChildren())
		{
			AppendData(child, builder, indentation + 1, child == Serialized->GetChildren().back());
		}

		if (Serialized->GetName().empty())
		{
			builder << indents.str() << "}\n";
		}
		else if (Serialized->GetValue().empty())
		{
			builder << indents.str();

			if (end)
			{
				builder << "}\n";
			}
			else
			{
				builder << "},\n";
			}
		}
	}

	std::shared_ptr<Serialized> JsonSection::Convert(const JsonSection &source, std::shared_ptr<Serialized> &parent, const bool &isTopSection)
	{
		auto thisValue = parent;

		if (!isTopSection)
		{
			thisValue = std::make_shared<Serialized>(source.m_name, "");
			parent->GetChildren().emplace_back(thisValue);
		}

		auto contentSplit = FormatString::Split(source.m_content, ",", true);

		for (auto &data : contentSplit)
		{
			auto dataSplit = FormatString::Split(data, ":", true);

			if (dataSplit.size() != 2 || dataSplit.at(0).empty() || dataSplit.at(1).empty())
			{
				continue;
			}

			std::string name = dataSplit.at(0).substr(1, dataSplit.at(0).size() - 2);
			auto newChild = std::make_shared<Serialized>(name, dataSplit.at(1));
			thisValue->GetChildren().emplace_back(newChild);
		}

		for (auto &child : source.m_children)
		{
			Convert(*child, thisValue, false);
		}

		return thisValue;
	}
}
