/*************************************************************************/
/*  translation.h                                                        */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2022 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2022 Godot Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#ifndef TRANSLATION_H
#define TRANSLATION_H

#include "core/io/resource.h"
#include "core/object/gdvirtual.gen.inc"
#include "core/object/script_language.h"

class Translation : public Resource {
	GDCLASS(Translation, Resource);
	OBJ_SAVE_TYPE(Translation);
	RES_BASE_EXTENSION("translation");

	String locale = "en";
	Map<StringName, StringName> translation_map;

	virtual Vector<String> _get_message_list() const;
	virtual Dictionary _get_messages() const;
	virtual void _set_messages(const Dictionary &p_messages);

protected:
	static void _bind_methods();

	GDVIRTUAL2RC(StringName, _get_message, StringName, StringName);
	GDVIRTUAL4RC(StringName, _get_plural_message, StringName, StringName, int, StringName);

public:
	void set_locale(const String &p_locale);
	_FORCE_INLINE_ String get_locale() const { return locale; }

	virtual void add_message(const StringName &p_src_text, const StringName &p_xlated_text, const StringName &p_context = "");
	virtual void add_plural_message(const StringName &p_src_text, const Vector<String> &p_plural_xlated_texts, const StringName &p_context = "");
	virtual StringName get_message(const StringName &p_src_text, const StringName &p_context = "") const; //overridable for other implementations
	virtual StringName get_plural_message(const StringName &p_src_text, const StringName &p_plural_text, int p_n, const StringName &p_context = "") const;
	virtual void erase_message(const StringName &p_src_text, const StringName &p_context = "");
	virtual void get_message_list(List<StringName> *r_messages) const;
	virtual int get_message_count() const;

	Translation() {}
};

class TranslationServer : public Object {
	GDCLASS(TranslationServer, Object);

	String locale = "en";
	String fallback;

	Set<Ref<Translation>> translations;
	Ref<Translation> tool_translation;
	Ref<Translation> doc_translation;

	Map<String, String> locale_name_map;

	bool enabled = true;

	bool pseudolocalization_enabled = false;
	bool pseudolocalization_accents_enabled = false;
	bool pseudolocalization_double_vowels_enabled = false;
	bool pseudolocalization_fake_bidi_enabled = false;
	bool pseudolocalization_override_enabled = false;
	bool pseudolocalization_skip_placeholders_enabled = false;
	bool editor_pseudolocalization = false;
	float expansion_ratio = 0.0;
	String pseudolocalization_prefix;
	String pseudolocalization_suffix;

	StringName tool_pseudolocalize(const StringName &p_message) const;
	String get_override_string(String &p_message) const;
	String double_vowels(String &p_message) const;
	String replace_with_accented_string(String &p_message) const;
	String wrap_with_fakebidi_characters(String &p_message) const;
	String add_padding(String &p_message, int p_length) const;
	const char32_t *get_accented_version(char32_t p_character) const;
	bool is_placeholder(String &p_message, int p_index) const;

	static TranslationServer *singleton;
	bool _load_translations(const String &p_from);

	StringName _get_message_from_translations(const StringName &p_message, const StringName &p_context, const String &p_locale, bool plural, const String &p_message_plural = "", int p_n = 0) const;

	static void _bind_methods();

public:
	_FORCE_INLINE_ static TranslationServer *get_singleton() { return singleton; }

	void set_enabled(bool p_enabled) { enabled = p_enabled; }
	_FORCE_INLINE_ bool is_enabled() const { return enabled; }

	void set_locale(const String &p_locale);
	String get_locale() const;
	Ref<Translation> get_translation_object(const String &p_locale);

	String get_locale_name(const String &p_locale) const;

	Array get_loaded_locales() const;

	void add_translation(const Ref<Translation> &p_translation);
	void remove_translation(const Ref<Translation> &p_translation);

	StringName translate(const StringName &p_message, const StringName &p_context = "") const;
	StringName translate_plural(const StringName &p_message, const StringName &p_message_plural, int p_n, const StringName &p_context = "") const;

	StringName pseudolocalize(const StringName &p_message) const;

	bool is_pseudolocalization_enabled() const;
	void set_pseudolocalization_enabled(bool p_enabled);
	void set_editor_pseudolocalization(bool p_enabled);
	void reload_pseudolocalization();

	static Vector<String> get_all_locales();
	static Vector<String> get_all_locale_names();
	static bool is_locale_valid(const String &p_locale);
	static String standardize_locale(const String &p_locale);
	static String get_language_code(const String &p_locale);

	String get_tool_locale();
	void set_tool_translation(const Ref<Translation> &p_translation);
	Ref<Translation> get_tool_translation() const;
	StringName tool_translate(const StringName &p_message, const StringName &p_context = "") const;
	StringName tool_translate_plural(const StringName &p_message, const StringName &p_message_plural, int p_n, const StringName &p_context = "") const;
	void set_doc_translation(const Ref<Translation> &p_translation);
	StringName doc_translate(const StringName &p_message, const StringName &p_context = "") const;
	StringName doc_translate_plural(const StringName &p_message, const StringName &p_message_plural, int p_n, const StringName &p_context = "") const;

	void setup();

	void clear();

	void load_translations();

	TranslationServer();
};

#endif // TRANSLATION_H
