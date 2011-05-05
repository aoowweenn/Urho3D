//
// Urho3D Engine
// Copyright (c) 2008-2011 Lasse ��rni
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#pragma once

#include "Object.h"
#include "UIBatch.h"

class Cursor;
class Graphics;
class ResourceCache;
class UIBatch;
class UIElement;
class XMLElement;
class XMLFile;

/// UI subsystem. Manages the graphical user interface
class UI : public Object
{
    OBJECT(UI);
    
public:
    /// Construct
    UI(Context* context);
    /// Destruct
    virtual ~UI();
    
    /// Set cursor UI element
    void SetCursor(Cursor* cursor);
    /// Set focused UI element
    void SetFocusElement(UIElement* element);
    /// Clear the UI (excluding the cursor)
    void Clear();
    /// Update the UI logic. Called by HandlePostUpdate()
    void Update(float timeStep);
    /// Update the UI for rendering. Called by HandlePostRenderUpdate()
    void RenderUpdate();
    /// Render the UI
    void Render();
    /// Load a UI layout from an XML file. Optionally specify another XML file for element style. Return the root element
    SharedPtr<UIElement> LoadLayout(XMLFile* file, XMLFile* styleFile = 0);
    /// Set clipboard text
    void SetClipBoardText(const std::string& text);
    
    /// Return root UI elemenet
    UIElement* GetRootElement() const { return rootElement_; }
    /// Return cursor
    Cursor* GetCursor() const { return cursor_; }
    /// Return UI element at screen coordinates
    UIElement* GetElementAt(const IntVector2& position, bool activeOnly = true);
    /// Return UI element at screen coordinates
    UIElement* GetElementAt(int x, int y, bool activeOnly = true);
    /// Return focused element
    UIElement* GetFocusElement() const;
    /// Return topmost enabled root-level element
    UIElement* GetFrontElement() const;
    /// Return cursor position
    IntVector2 GetCursorPosition();
    /// Return clipboard text
    const std::string& GetClipBoardText() const { return clipBoard_; }
    
private:
    /// Initialize when screen mode initially set
    void Initialize();
    /// Update UI element logic recursively
    void Update(float timeStep, UIElement* element);
    /// Generate batches from an UI element recursively
    void GetBatches(UIElement* element, IntRect currentScissor);
    /// Return UI element at screen position recursively
    void GetElementAt(UIElement*& result, UIElement* current, const IntVector2& position, bool activeOnly);
    /// Load a UI layout from an XML file recursively
    void LoadLayout(UIElement* current, const XMLElement& elem, XMLFile* styleFile);
    /// Handle screen mode event
    void HandleScreenMode(StringHash eventType, VariantMap& eventData);
    /// Handle mouse move event
    void HandleMouseMove(StringHash eventType, VariantMap& eventData);
    /// Handle mouse button down event
    void HandleMouseButtonDown(StringHash eventType, VariantMap& eventData);
    /// Handle mouse button up event
    void HandleMouseButtonUp(StringHash eventType, VariantMap& eventData);
    /// Handle mouse wheel event
    void HandleMouseWheel(StringHash eventType, VariantMap& eventData);
    /// Handle keypress event
    void HandleKeyDown(StringHash eventType, VariantMap& eventData);
    /// Handle character event
    void HandleChar(StringHash eventType, VariantMap& eventData);
    /// Handle logic post-update event
    void HandlePostUpdate(StringHash eventType, VariantMap& eventData);
    /// Handle render update event
    void HandleRenderUpdate(StringHash eventType, VariantMap& eventData);
    
    /// Graphics
    WeakPtr<Graphics> graphics_;
    /// Resource cache
    WeakPtr<ResourceCache> cache_;
    /// Vertex shader for no texture
    SharedPtr<VertexShader> noTextureVS_;
    /// Vertex shader for diffuse texture
    SharedPtr<VertexShader> diffTextureVS_;
    /// Pixel shader for no texture
    SharedPtr<PixelShader> noTexturePS_;
    /// Pixel shader for diffuse texture
    SharedPtr<PixelShader> diffTexturePS_;
    /// Pixel shader for alpha texture
    SharedPtr<PixelShader> alphaTexturePS_;
    /// UI root element
    SharedPtr<UIElement> rootElement_;
    /// Cursor
    SharedPtr<Cursor> cursor_;
    /// UI rendering batches
    std::vector<UIBatch> batches_;
    /// UI rendering quads
    std::vector<UIQuad> quads_;
    /// UI element being dragged
    WeakPtr<UIElement> dragElement_;
    /// Element to defocus on the next update
    WeakPtr<UIElement> defocusElement_;
    /// Clipboard text
    std::string clipBoard_;
    /// Mouse buttons held down
    int mouseButtons_;
    /// Qualifier keys held down
    int qualifiers_;
    /// Initialized flag
    bool initialized_;
};

/// Register UI library objects
void RegisterUILibrary(Context* context);
