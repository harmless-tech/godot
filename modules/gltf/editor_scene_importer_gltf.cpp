/*************************************************************************/
/*  editor_scene_importer_gltf.cpp                                       */
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

#if TOOLS_ENABLED
#include "editor_scene_importer_gltf.h"

#include "gltf_document.h"
#include "gltf_state.h"

#include "scene/3d/node_3d.h"
#include "scene/animation/animation_player.h"
#include "scene/resources/animation.h"

uint32_t EditorSceneFormatImporterGLTF::get_import_flags() const {
	return ImportFlags::IMPORT_SCENE | ImportFlags::IMPORT_ANIMATION;
}

void EditorSceneFormatImporterGLTF::get_extensions(List<String> *r_extensions) const {
	r_extensions->push_back("gltf");
	r_extensions->push_back("glb");
}

Node *EditorSceneFormatImporterGLTF::import_scene(const String &p_path,
		uint32_t p_flags, int p_bake_fps,
		List<String> *r_missing_deps,
		Error *r_err) {
	Ref<GLTFDocument> doc;
	doc.instantiate();
	return doc->import_scene_gltf(p_path, p_flags, p_bake_fps, Ref<GLTFState>(), r_missing_deps, r_err);
}

Ref<Animation> EditorSceneFormatImporterGLTF::import_animation(const String &p_path,
		uint32_t p_flags,
		int p_bake_fps) {
	return Ref<Animation>();
}

#endif // TOOLS_ENABLED
