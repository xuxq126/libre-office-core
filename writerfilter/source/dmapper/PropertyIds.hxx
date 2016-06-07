/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */
#ifndef INCLUDED_WRITERFILTER_SOURCE_DMAPPER_PROPERTYIDS_HXX
#define INCLUDED_WRITERFILTER_SOURCE_DMAPPER_PROPERTYIDS_HXX

namespace writerfilter {
namespace dmapper{
enum PropertyIds
    {
        PROP_ID_START = 1
        ,META_PROP_CELL_MAR_BOTTOM = PROP_ID_START
        ,META_PROP_CELL_MAR_LEFT
        ,META_PROP_CELL_MAR_RIGHT
        ,META_PROP_CELL_MAR_TOP
        ,META_PROP_HORIZONTAL_BORDER
        ,META_PROP_TABLE_STYLE_NAME
        ,META_PROP_VERTICAL_BORDER
        ,PROP_ADD_EXTERNAL_LEADING
        ,PROP_ADD_PARA_TABLE_SPACING
        ,PROP_ADJUST
        ,PROP_ADJUST_CONTRAST
        ,PROP_ADJUST_LUMINANCE
        ,PROP_ALTERNATIVE_TEXT
        ,PROP_ANCHOR_TYPE
        ,PROP_AUTOMATIC_DISTANCE
        ,PROP_BACK_COLOR
        ,PROP_BACK_COLOR_TRANSPARENCY
        ,PROP_BITMAP
        ,PROP_BOTTOM_BORDER
        ,PROP_BOTTOM_BORDER_DISTANCE
        ,PROP_BOTTOM_MARGIN
        ,PROP_BREAK_TYPE
        ,PROP_BULLET_CHAR
        ,PROP_BULLET_FONT_NAME
        ,PROP_CHAPTER_FORMAT
        ,PROP_CHARACTER_STYLES
        ,PROP_CHAR_AUTO_KERNING
        ,PROP_CHAR_BACK_COLOR
        ,PROP_CHAR_CASE_MAP
        ,PROP_CHAR_CHAR_KERNING
        ,PROP_CHAR_COLOR
        ,PROP_CHAR_COMBINE_IS_ON
        ,PROP_CHAR_COMBINE_PREFIX
        ,PROP_CHAR_COMBINE_SUFFIX
        ,PROP_CHAR_CONTOURED
        ,PROP_CHAR_LEFT_BORDER
        ,PROP_CHAR_RIGHT_BORDER
        ,PROP_CHAR_TOP_BORDER
        ,PROP_CHAR_BOTTOM_BORDER
        ,PROP_CHAR_LEFT_BORDER_DISTANCE
        ,PROP_CHAR_RIGHT_BORDER_DISTANCE
        ,PROP_CHAR_TOP_BORDER_DISTANCE
        ,PROP_CHAR_BOTTOM_BORDER_DISTANCE
        ,PROP_CHAR_EMPHASIS
        ,PROP_CHAR_ESCAPEMENT
        ,PROP_CHAR_ESCAPEMENT_HEIGHT
        ,PROP_CHAR_FLASH
        ,PROP_CHAR_FONT_CHAR_SET
        ,PROP_CHAR_FONT_CHAR_SET_ASIAN
        ,PROP_CHAR_FONT_CHAR_SET_COMPLEX
        ,PROP_CHAR_FONT_FAMILY
        ,PROP_CHAR_FONT_FAMILY_ASIAN
        ,PROP_CHAR_FONT_FAMILY_COMPLEX
        ,PROP_CHAR_FONT_NAME
        ,PROP_CHAR_FONT_NAME_ASIAN
        ,PROP_CHAR_FONT_NAME_COMPLEX
        ,PROP_CHAR_FONT_PITCH
        ,PROP_CHAR_FONT_PITCH_ASIAN
        ,PROP_CHAR_FONT_PITCH_COMPLEX
        ,PROP_CHAR_FONT_STYLE
        ,PROP_CHAR_FONT_STYLE_ASIAN
        ,PROP_CHAR_FONT_STYLE_COMPLEX
        ,PROP_CHAR_HEIGHT
        ,PROP_CHAR_HEIGHT_ASIAN
        ,PROP_CHAR_HEIGHT_COMPLEX
        ,PROP_CHAR_HIDDEN
        ,PROP_CHAR_HIGHLIGHT
        ,PROP_CHAR_LOCALE
        ,PROP_CHAR_LOCALE_ASIAN
        ,PROP_CHAR_LOCALE_COMPLEX
        ,PROP_CHAR_POSTURE
        ,PROP_CHAR_POSTURE_ASIAN
        ,PROP_CHAR_POSTURE_COMPLEX
        ,PROP_CHAR_PROP_HEIGHT
        ,PROP_CHAR_PROP_HEIGHT_ASIAN
        ,PROP_CHAR_PROP_HEIGHT_COMPLEX
        ,PROP_CHAR_RELIEF
        ,PROP_CHAR_ROTATION
        ,PROP_CHAR_ROTATION_IS_FIT_TO_LINE
        ,PROP_CHAR_SHADOW_FORMAT
        ,PROP_CHAR_SCALE_WIDTH
        ,PROP_CHAR_SHADOWED
        ,PROP_CHAR_STRIKEOUT
        ,PROP_CHAR_STYLE_NAME
        ,PROP_CHAR_UNDERLINE
        ,PROP_CHAR_UNDERLINE_COLOR
        ,PROP_CHAR_UNDERLINE_HAS_COLOR
        ,PROP_CHAR_WEIGHT
        ,PROP_CHAR_WEIGHT_ASIAN
        ,PROP_CHAR_WEIGHT_COMPLEX
        ,PROP_CHAR_WORD_MODE
        ,PROP_CONTENT
        ,PROP_CONTOUR_OUTSIDE
        ,PROP_CONTOUR_POLY_POLYGON
        ,PROP_COUNT_EMPTY_LINES
        ,PROP_COUNT_LINES_IN_FRAMES
        ,PROP_CREATE_FROM_LEVEL_PARAGRAPH_STYLES
        ,PROP_CREATE_FROM_MARKS
        ,PROP_CREATE_FROM_OUTLINE
        ,PROP_CURRENT_PRESENTATION
        ,PROP_DATA_COLUMN_NAME
        ,PROP_DEFAULT
        ,PROP_DELETE
        ,PROP_DESCRIPTION
        ,PROP_DISTANCE
        ,PROP_DROP_CAP_FORMAT
        ,PROP_FILE_FORMAT
        ,PROP_FIRST_LINE_INDENT
        ,PROP_FIRST_LINE_OFFSET
        ,PROP_FIRST_PAGE
        ,PROP_FOOTER_BODY_DISTANCE
        ,PROP_FOOTER_DYNAMIC_SPACING
        ,PROP_FOOTER_HEIGHT
        ,PROP_FOOTER_IS_DYNAMIC_HEIGHT
        ,PROP_FOOTER_IS_ON
        ,PROP_FOOTER_IS_SHARED
        ,PROP_FOOTER_TEXT
        ,PROP_FOOTER_TEXT_LEFT
        ,PROP_FOOTNOTE_COUNTING
        ,PROP_FORMAT
        ,PROP_FULL_NAME
        ,PROP_GAMMA
        ,PROP_GRAPHIC
        ,PROP_GRAPHIC_COLOR_MODE
        ,PROP_GRAPHIC_CROP
        ,PROP_GRID_BASE_HEIGHT
        ,PROP_GRID_DISPLAY
        ,PROP_GRID_LINES
        ,PROP_GRID_MODE
        ,PROP_GRID_PRINT
        ,PROP_GRID_RUBY_HEIGHT
        ,PROP_HEADER_BODY_DISTANCE
        ,PROP_HEADER_DYNAMIC_SPACING
        ,PROP_HEADER_HEIGHT
        ,PROP_HEADER_IS_DYNAMIC_HEIGHT
        ,PROP_HEADER_IS_ON
        ,PROP_HEADER_IS_SHARED
        ,PROP_HEADER_ROW_COUNT
        ,PROP_HEADER_TEXT
        ,PROP_HEADER_TEXT_LEFT
        ,PROP_HEADING_STYLE_NAME
        ,PROP_HEIGHT
        ,PROP_HELP
        ,PROP_HINT
        ,PROP_HORI_MIRRORED_ON_EVEN_PAGES
        ,PROP_HORI_MIRRORED_ON_ODD_PAGES
        ,PROP_HORI_ORIENT
        ,PROP_HORI_ORIENT_POSITION
        ,PROP_HORI_ORIENT_RELATION
        ,PROP_HYPER_LINK_U_R_L
        ,PROP_INDENT_AT
        ,PROP_INPUT_STREAM
        ,PROP_INSERT
        ,PROP_INTERVAL
        ,PROP_IS_AUTO_HEIGHT
        ,PROP_IS_DATE
        ,PROP_IS_FIXED
        ,PROP_IS_INPUT
        ,PROP_IS_LANDSCAPE
        ,PROP_IS_ON
        ,PROP_IS_SPLIT_ALLOWED
        ,PROP_IS_VISIBLE
        ,PROP_KEYWORDS
        ,PROP_LABEL_CATEGORY
        ,PROP_LEFT_BORDER
        ,PROP_LEFT_BORDER_DISTANCE
        ,PROP_LEFT_MARGIN
        ,PROP_LEVEL
        ,PROP_LEVEL_FOLLOW
        ,PROP_LEVEL_FORMAT
        ,PROP_LEVEL_PARAGRAPH_STYLES
        ,PROP_LISTTAB_STOP_POSITION
        ,PROP_MACRO_NAME
        ,PROP_NAME
        ,PROP_NUMBERING_LEVEL
        ,PROP_NUMBERING_RULES
        ,PROP_NUMBERING_STYLE_NAME
        ,PROP_NUMBERING_TYPE
        ,PROP_NUMBER_FORMAT
        ,PROP_NUMBER_POSITION
        ,PROP_OPAQUE
        ,PROP_OUTLINE_LEVEL
        ,PROP_PAGE_DESC_NAME
        ,PROP_PAGE_NUMBER_OFFSET
        ,PROP_PAGE_TOGGLE
        ,PROP_PARAGRAPH_FORMAT
        ,PROP_PARAGRAPH_STYLES
        ,PROP_PARAGRAPH_STYLE_NAME
        ,PROP_PARA_ADJUST
        ,PROP_PARA_BACK_COLOR
        ,PROP_PARA_BOTTOM_MARGIN
        ,PROP_PARA_FIRST_LINE_INDENT
        ,PROP_PARA_IS_HANGING_PUNCTUATION
        ,PROP_PARA_IS_HYPHENATION
        ,PROP_PARA_KEEP_TOGETHER
        ,PROP_PARA_LAST_LINE_ADJUST
        ,PROP_PARA_LEFT_MARGIN
        ,PROP_PARA_LINE_NUMBER_COUNT
        ,PROP_PARA_LINE_NUMBER_START_VALUE
        ,PROP_PARA_LINE_SPACING
        ,PROP_PARA_ORPHANS
        ,PROP_PARA_RIGHT_MARGIN
        ,PROP_PARA_SPLIT
        ,PROP_PARA_STYLE_NAME
        ,PROP_PARA_TAB_STOPS
        ,PROP_PARA_TOP_MARGIN
        ,PROP_PARA_VERT_ALIGNMENT
        ,PROP_PARA_WIDOWS
        ,PROP_PARENT_NUMBERING
        ,PROP_POSITION_AND_SPACE_MODE
        ,PROP_POSITION_PROTECTED
        ,PROP_PREFIX
        ,PROP_PRINTER_PAPER_TRAY_INDEX
        ,PROP_REDLINE_AUTHOR
        ,PROP_REDLINE_COMMENT
        ,PROP_REDLINE_DATE_TIME
        ,PROP_REDLINE_IDENTIFIER
        ,PROP_REDLINE_SUCCESSOR_DATA
        ,PROP_REDLINE_TYPE
        ,PROP_REDLINE_TOKEN
        ,PROP_REDLINE_REVERT_PROPERTIES
        ,PROP_REFERENCE_FIELD_PART
        ,PROP_REFERENCE_FIELD_SOURCE
        ,PROP_RESTART_AT_EACH_PAGE
        ,PROP_RIGHT_BORDER
        ,PROP_RIGHT_BORDER_DISTANCE
        ,PROP_RIGHT_MARGIN
        ,PROP_SEPARATOR_LINE_IS_ON
        ,PROP_SERVICE_CHAR_STYLE
        ,PROP_SERVICE_PARA_STYLE
        ,PROP_SIZE
        ,PROP_SIZE100th_M_M
        ,PROP_SIZE_PIXEL
        ,PROP_SIZE_PROTECTED
        ,PROP_SIZE_TYPE
        ,PROP_SOURCE_NAME
        ,PROP_STANDARD
        ,PROP_START_AT
        ,PROP_START_WITH
        ,PROP_STREAM_NAME
        ,PROP_SUBJECT
        ,PROP_SUB_TYPE
        ,PROP_SUFFIX
        ,PROP_SURROUND
        ,PROP_SURROUND_CONTOUR
        ,PROP_TABLE_BORDER
        ,PROP_TABLE_BORDER_DISTANCES
        ,PROP_TABLE_COLUMN_SEPARATORS
        ,PROP_TABLE_REDLINE_PARAMS
        ,PROP_TABLE_REDLINE_AUTHOR
        ,PROP_TABLE_REDLINE_DATE
        ,PROP_TABLE_REDLINE_ID
        ,PROP_TABLE_REDLINE_TOKEN
        ,PROP_TABLE_ROW_DELETE
        ,PROP_TABLE_ROW_INSERT
        ,PROP_TABLE_CELL_DELETE
        ,PROP_TABLE_CELL_INSERT
        ,PROP_TABS_RELATIVE_TO_INDENT
        ,PROP_TAB_STOP_DISTANCE
        ,PROP_TEXT
        ,PROP_TEXT_COLUMNS
        ,PROP_TEXT_RANGE
        ,PROP_TEXT_VERTICAL_ADJUST
        ,PROP_TITLE
        ,PROP_TOKEN_CHAPTER_INFO
        ,PROP_TOKEN_HYPERLINK_END
        ,PROP_TOKEN_HYPERLINK_START
        ,PROP_TOKEN_TEXT
        ,PROP_TOKEN_TYPE
        ,PROP_TOP_BORDER
        ,PROP_TOP_BORDER_DISTANCE
        ,PROP_TOP_MARGIN
        ,PROP_USER_DATA_TYPE
        ,PROP_VERTICAL_MERGE
        ,PROP_VERT_MIRRORED
/*254*/ ,PROP_GRID_STANDARD_MODE
        ,PROP_VERT_ORIENT
        ,PROP_VERT_ORIENT_POSITION
        ,PROP_VERT_ORIENT_RELATION
        ,PROP_WIDTH
        ,PROP_WIDTH_TYPE
        ,PROP_TBL_LOOK
        ,PROP_WRITING_MODE
/*253*/ ,PROP_FRM_DIRECTION
        ,PROP_EMBEDDED_OBJECT
        ,PROP_PARA_CONTEXT_MARGIN
        ,PROP_PAGE_STYLE_LAYOUT
        ,PROP_Z_ORDER
        ,PROP_EMBED_FONTS
        ,PROP_EMBED_SYSTEM_FONTS
        ,PROP_SHADOW_FORMAT
        ,PROP_RELATIVE_WIDTH
        ,PROP_IS_WIDTH_RELATIVE
        ,PROP_GRAPHIC_URL
        ,PROP_GRAPHIC_BITMAP
        ,PROP_CHAR_SHADING_VALUE
        ,PROP_CHAR_SHADING_MARKER
        ,PROP_FIRST_IS_SHARED
        ,PROP_MIRROR_INDENTS
        ,PROP_SURROUND_TEXT_WRAP_SMALL
        ,PROP_PARA_SHADOW_FORMAT
        ,PROP_FOOTNOTE_LINE_RELATIVE_WIDTH
        ,PROP_PARA_TOP_MARGIN_BEFORE_AUTO_SPACING
        ,PROP_PARA_BOTTOM_MARGIN_AFTER_AUTO_SPACING
        ,PROP_TBL_HEADER
        ,PROP_CHAR_THEME_NAME_ASCII
        ,PROP_CHAR_THEME_NAME_CS
        ,PROP_CHAR_THEME_NAME_H_ANSI
        ,PROP_CHAR_THEME_NAME_EAST_ASIA
        ,PROP_CHAR_THEME_FONT_NAME_ASCII
        ,PROP_CHAR_THEME_FONT_NAME_CS
        ,PROP_CHAR_THEME_FONT_NAME_H_ANSI
        ,PROP_CHAR_THEME_FONT_NAME_EAST_ASIA
        ,PROP_CHAR_THEME_COLOR
        ,PROP_CHAR_THEME_ORIGINAL_COLOR
        ,PROP_CHAR_THEME_COLOR_SHADE
        ,PROP_CHAR_THEME_FILL
        ,PROP_HORIZONTAL_MERGE
        ,PROP_HIDE_TAB_LEADER_AND_PAGE_NUMBERS
        ,PROP_TAB_IN_TOC
        ,PROP_TOC_BOOKMARK
        ,PROP_TOC_NEW_LINE
        ,PROP_TOC_PARAGRAPH_OUTLINE_LEVEL
        ,PROP_CHAR_THEME_COLOR_TINT
        ,PROP_CHAR_GLOW_TEXT_EFFECT
        ,PROP_CHAR_SHADOW_TEXT_EFFECT
        ,PROP_CHAR_REFLECTION_TEXT_EFFECT
        ,PROP_CHAR_TEXTOUTLINE_TEXT_EFFECT
        ,PROP_CHAR_TEXTFILL_TEXT_EFFECT
        ,PROP_CHAR_SCENE3D_TEXT_EFFECT
        ,PROP_CHAR_PROPS3D_TEXT_EFFECT
        ,PROP_CHAR_LIGATURES_TEXT_EFFECT
        ,PROP_CHAR_NUMFORM_TEXT_EFFECT
        ,PROP_CHAR_NUMSPACING_TEXT_EFFECT
        ,PROP_CHAR_STYLISTICSETS_TEXT_EFFECT
        ,PROP_CHAR_CNTXTALTS_TEXT_EFFECT
        ,PROP_SDTPR
        ,PROP_CELL_INTEROP_GRAB_BAG
        ,PROP_TABLE_INTEROP_GRAB_BAG
        ,PROP_INDEX_ENTRY_TYPE
        ,PROP_APPLY_PARAGRAPH_MARK_FORMAT_TO_NUMBERING
        ,PROP_CELL_DIRECTION
        ,PROP_SDT_END_BEFORE
        ,PROP_PARA_SDT_END_BEFORE
        ,META_PROP_TABLE_LOOK
        ,PROP_PARA_CNF_STYLE
        ,PROP_CELL_CNF_STYLE
        ,PROP_ROW_CNF_STYLE
        ,PROP_CELL_HIDE_MARK
        ,PROP_FOLLOW_TEXT_FLOW
        ,PROP_FILL_STYLE
        ,PROP_FILL_COLOR
        ,PROP_SNAP_TO_GRID
        ,PROP_GRID_SNAP_TO_CHARS
        ,PROP_RUBY_STYLE
        ,PROP_RUBY_TEXT
        ,PROP_RUBY_ADJUST
    };

//Returns the UNO string equivalent to eId.
OUString getPropertyName(PropertyIds eId);

} //namespace dmapper
} // namespace writerfilter
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
