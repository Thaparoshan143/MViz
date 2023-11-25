#pragma once

#include<iostream>
#include<map>
#include"./Types.h"

typedef void (*ClickEventCallback)();

namespace Abs
{
    typedef enum EventCallType
    {
        ONCLICK = 1,
        ONCHANGE = 2,
    }EventCallType;

    typedef enum UIElementType
    {
        PANEL = 1,
        BUTTON = 2,
        INPUTFIELD = 3,
    }UIElementType;

    typedef enum UITextType
    {
        TITLE = 1,
        LABEL = 2,
        FIELDTEXT = 3,
        PLACEHOLDER = 4,
    }UITextType;

    // All the struct are defined for UI props, useful to pass only ui props when adding element in UI so...
    struct _UIProps
    {
        public:
        _UIProps(fVec2 p, fVec2 d, Color bgCol, ClickEventCallback clickCallback=nullptr)
        {
            _pos = p;
            _dim = d;
            _bgCol = bgCol;
            _onClickEvent = clickCallback;
        }

        fVec2 _pos, _dim;
        fVec3 _bgCol;
        ClickEventCallback _onClickEvent;
        UIElementType _type;
    };

    struct ButtonProps : public _UIProps
    {
        public:
        ButtonProps(fVec2 p, fVec2 d, Color bc, String l, ClickEventCallback cEvent) : _UIProps(p,d,bc, cEvent)
        {
            _label = l;
            _type = BUTTON;
        }

        String _label;
    };

    struct PanelProps : public _UIProps
    {
        public:
        PanelProps(fVec2 p, fVec2 d, Color bc, String t, ClickEventCallback cEvent) : _UIProps(p,d,bc, cEvent)
        {
            _title = t;
            _type = PANEL;
        }

        String _title;
    };

    struct InputFieldProps : public _UIProps 
    {
        public:
        InputFieldProps(fVec2 p, fVec2 d, Color bc, String placeHol, ClickEventCallback clickEvent, ClickEventCallback changeEvent, String t="") : _UIProps(p,d,bc, clickEvent)
        {
            _text = t;
            _placeholder = placeHol;
            _type = INPUTFIELD;
            _onChangeEvent = changeEvent;
        }

        String _text;
        String _placeholder;
        ClickEventCallback _onChangeEvent;
    };


    class _BaseUI
    {
        public:
        _BaseUI(){}

        inline fVec2 GetPos() {    return m_pos;   }
        inline fVec2 GetDim() {    return m_dim;   }
        inline Color GetBgCol() {    return m_bgCol;   }
        inline UIElementType GetType()  {   return m_type;  }
        inline bool IsOfType(UIElementType eleType) {   return (m_type == eleType);    }

        // These are just helper methods ...
        // figure out which scale using either -1 to 1 or the screen real scale to return the actual working border point..
        // for now returning for -1 to 1 scale state.. review for future
        static fVec4 getBorder(fVec2 pos, fVec2 dim)
        {
            // returing the x and y cordinates to check whether the mouse is withing the boundry region or not..
            return fVec4(pos.x-dim.x/2.0, pos.y+dim.y/2.0, pos.x+dim.x/2.0, pos.y-dim.y/2.0);
        }

        static bool withinBoundary(fVec4 border, fVec2 pos)
        {
            return border.x < pos.x && border.y > pos.y && border.z > pos.x  && border.w < pos.y;
        }

        // Initialization will be done by derived class in accordance of the props passed..
        fVec2 m_pos;
        fVec2 m_dim;
        fVec3 m_bgCol;
        UIElementType m_type;
    };

    class _InteractableUI : public _BaseUI
    {
        public:
        virtual bool OnClick(dVec2 mouPos, int mouCode)
        {
            if(withinBoundary(getBorder(m_pos, m_dim), mouPos))
            {
                m_isActive = true;
                if(m_onClickEvent!=nullptr)
                {
                    m_onClickEvent();
                }
                else
                {
                    std::cout << "On Click event not attached" << std::endl;
                }
            }
            else {  return (m_isActive=false);   }
        };

        virtual _BaseUI* GetSubscriber() = 0;

        virtual ClickEventCallback GetEventCallback(EventCallType ect)
        {
            if(ect==ONCLICK)
            {
                return m_onClickEvent;
            }
            else
            {
                std::cout << "Doesn't contain the eventcallback as requested!!" << std::endl;
            }
        }

        ClickEventCallback m_onClickEvent;
        bool m_isActive;
        bool m_isClickable;
    };

    class Panel : public _InteractableUI
    {
        public:
        Panel(PanelProps panInfo)
        {
            m_pos = panInfo._pos;   m_dim = panInfo._dim;   m_bgCol = panInfo._bgCol;
            m_onClickEvent = panInfo._onClickEvent; m_title = panInfo._title;   m_type = panInfo._type;
        }

        void AttachElement(_InteractableUI *newEle)
        {
            if(m_elementList.count(newEle->GetType())==0)
            {
                std::vector<_InteractableUI*> eleList;
                eleList.push_back(newEle);
                m_elementList.insert({  newEle->GetType(), eleList });
            }
            else
            {
                m_elementList[newEle->GetType()].push_back(newEle);
            }
        }
        
        void AttachElements(std::vector<_InteractableUI> *newEles)
        {
            for(int i=0;i<newEles->size();i++)
            {
                AttachElement(&((*newEles)[i]));
            }
        }

        bool OnClick(dVec2 mouPos, int mouCode) override
        {
            if(withinBoundary(getBorder(m_pos, m_dim), mouPos))
            {   
                m_isActive = true;
                dispatchMouseEventsOfElements(mouPos, mouCode);
                return true;    
            }
            else {  return (m_isActive=false);   }
        }

        _BaseUI* GetSubscriber() override  
        {   
            for(const auto &item : m_elementList)
            {
                for(int i=0;i<item.second.size();i++)
                {
                    _BaseUI *temp = item.second[i]->GetSubscriber();
                    if(temp!=nullptr && temp->IsOfType(UIElementType::INPUTFIELD))
                    {
                        return temp;
                    }
                }
            }
            return nullptr;
        }

        inline String GetText(UITextType textType) {  return ((textType==TITLE)?m_title:""); }
        inline String* GetRawText(UITextType textType) {  return (textType==TITLE?(&m_title):nullptr); }

        String m_title;
        // currently all the UI we will be using are interactable UI so only creating list for storing it.. if other required make pointer of _BaseUI and move accordingly onclick...
        std::map<UIElementType, std::vector<_InteractableUI*> > m_elementList;

        void dispatchMouseEventsOfElements(dVec2 mouPos, int mouCode)
        {
            for(const auto& item: m_elementList)
            {
                for(int i=0;i<item.second.size();i++)
                {
                    item.second[i]->OnClick(mouPos, mouCode);
                }
            }
        }
    };

    class Button : public _InteractableUI
    {
        public:
        Button(ButtonProps btnInfo)
        {
            m_pos = btnInfo._pos;   m_dim = btnInfo._dim;   m_bgCol = btnInfo._bgCol;   m_onClickEvent = btnInfo._onClickEvent;
            m_label = btnInfo._label;   m_type = btnInfo._type;
        }

        _BaseUI* GetSubscriber() override  {   return m_isActive ? this : nullptr;    }

        inline String GetText(UITextType textType) {  return ((textType==LABEL)?m_label:""); }
        inline String* GetRawText(UITextType textType) {  return (textType==LABEL?(&m_label):nullptr); }

        String m_label;
    };

    class InputField : public _InteractableUI
    {
        public:
        InputField(InputFieldProps fieldInfo)
        {
            m_pos = fieldInfo._pos;   m_dim = fieldInfo._dim;   m_bgCol = fieldInfo._bgCol;   m_onClickEvent = fieldInfo._onClickEvent;
            m_onChangeEvent = fieldInfo._onChangeEvent; m_fieldText = fieldInfo._placeholder;  m_placeholder = fieldInfo._placeholder;  m_type = fieldInfo._type;
        }

        ClickEventCallback GetEventCallback(EventCallType ect) override
        {
            if(ect==ONCLICK)
            {
                return m_onClickEvent;
            }
            else if(ect==ONCHANGE)
            {
                return m_onChangeEvent;
            }
            else
            {
                std::cout << "Doesn't contain the eventcallback as requested!!";
            }
        }

        bool OnClick(dVec2 mouPos, int mouCode) override 
        {   
            _InteractableUI::OnClick(mouPos, mouCode);
            if(m_isActive && m_fieldText==m_placeholder)
                m_fieldText.clear();
            else if(!m_isActive && m_fieldText=="")
            {
                m_fieldText = m_placeholder;
            }
            return m_isActive;
        }

        bool IsActive() {   return m_isActive;  }

        _BaseUI* GetSubscriber() override {    return m_isActive ? this : nullptr;    }

        inline String GetText(UITextType textType)
        {  
            return ((textType==FIELDTEXT)?m_fieldText:(textType==PLACEHOLDER)?m_placeholder:"");
        }
        inline String* GetRawText(UITextType textType)
        {  
            return (textType==FIELDTEXT?(&m_fieldText):(textType==PLACEHOLDER)?(&m_placeholder):nullptr); 
        }

        // Currently there is no method exposed to change the place holder.. if needed use enum in above or make copy..., for now not letting user to change placeholder once initalize using props..
        virtual void OnFieldChange()
        {
            if(m_onChangeEvent!=nullptr)
                m_onChangeEvent();
            else
                std::cout << "On change event not attached to input field" << std::endl;
        }

        ClickEventCallback m_onChangeEvent;
        String m_fieldText, m_placeholder;
    };

    class UIManager
    {
        public:
        UIManager() {}

        // method exposed to update the window target of the UI manager..
        void UpdateTarget(void *target)   {   m_targetWindow = target;  }
        // There is no checking for if id exists or not .. for now, if reuqired might need to be added..
        virtual void AttachPanel(String id, Panel *newPan)
        {
            m_panelList.insert({id, newPan});
        }

        virtual void Render() = 0;

        virtual void DispatchMouseEvents(dVec2 mouPos, int mouCode)
        {
            m_keySubscriber = nullptr;
            if(m_isActive)
            {
                // Responsibility of UI mananger to figure out how to pass and dispatch the clickevent datas..
                // Note : Mouse position might need to be normalize before passing depending upon the scale used either -1 to 1, or screen size...
                for(const auto &item : m_panelList)
                {
                    if(item.second->OnClick(mouPos, mouCode))
                    {
                        std::cout << item.first << " -- On Click triggered--" << std::endl;
                        InputField *temp = (InputField*)item.second->GetSubscriber();
                        if(temp!=nullptr)
                        {
                            std::cout << "Subscriber found !" << std::endl;
                            m_keySubscriber = temp;
                        }
                    }
                }
            }
            else
            {
                std::cout << "UI not active to dispatch mouse event!" << std::endl;
            }
        }

        // We are currently using directly input field as the subscriber and letting it be manipualted later..
        void *m_targetWindow;
        InputField *m_keySubscriber;
        bool m_isActive;
        std::map<String, Panel*> m_panelList;
    };
}