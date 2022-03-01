#include "DictionaryLib.h"

std::string ToLower(const std::string& string)
{
	std::string result;
	std::transform(
		string.begin(),
		string.end(),
		std::back_inserter(result),
		[](char ch) {
			return std::tolower(ch);
		});

	return result;
}

void Trim(std::string& string)
{
	string.erase(string.find_last_not_of(' ') + 1);
	string.erase(0, string.find_first_not_of(' '));
}

Translations ParseStringForTranslations(const std::string& translationsString)
{
	std::stringstream ss(translationsString);
	std::string translation;
	Translations result;

	while (std::getline(ss, translation, ','))
	{
		Trim(translation);
		if (!translation.empty())
		{
			result.insert(translation);
		}
	}

	return result;
}

std::string SerializeTranslationsAsString(const Translations& translations)
{
	std::string result;
	auto last = translations.end();
	--last;
	for (auto it = translations.begin(); it != translations.end(); ++it)
	{
		result.append(*it);
		if (it != last)
		{
			result.append(", ");
		}
	}

	return result;
}

std::optional<Translations> LookupTranslation(const Dictionary& dictionary, const std::string& phrase)
{
	try
	{
		return dictionary.at(ToLower(phrase));
	}
	catch (const std::out_of_range&)
	{
		return std::nullopt;
	}
}

void AddDirectTranslations(Dictionary& dictionary, const std::string& phrase, const Translations& translations)
{
	auto const sourceInLower = ToLower(phrase);
	auto it = dictionary.find(sourceInLower);
	if (it == dictionary.end())
	{
		dictionary[sourceInLower] = translations;
	}
	else
	{
		it->second.insert(translations.begin(), translations.end());
	}
}

void AddReverseTranslations(Dictionary& dictionary, const Translations& translations, const std::string& phrase)
{
	for (auto const& translation : translations)
	{
		auto const translationInLower = ToLower(translation);
		auto it = dictionary.find(translationInLower);
		if (it == dictionary.end())
		{
			dictionary[translationInLower] = { phrase };
		}
		else
		{
			it->second.insert(phrase);
		}
	}
}

void AddTranslations(Dictionary& dictionary, const std::string& phrase, const Translations& translations)
{
	AddDirectTranslations(dictionary, phrase, translations);
	AddReverseTranslations(dictionary, translations, phrase);
}

void AddTranslations(Dictionary& dictionary, const std::string& phrase, const std::string& translationsString)
{
	auto const translations = ParseStringForTranslations(translationsString);
	if (translations.empty())
	{
		throw std::invalid_argument("empty translation");
	}

	AddTranslations(dictionary, phrase, translations);
}
