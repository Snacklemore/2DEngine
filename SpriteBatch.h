#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

// Number of frames a batch can be empty for before it is destroyed

#include <vector>
#include <array>
#include <random>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Texture.h"
#include "C_Sprite.h"


namespace moony
{
    class SpriteBatch : public sf::Drawable
    {
    public:
        void clear();
        void draw(C_Sprite& sprite);
        void order();

    private:
        struct Batch
        {
            void clear()
            {
                if(m_count > 0)
                {
                    //m_batches[i].m_count = m_batches[i].m_reserved;
                    m_count = 0;
                    m_inactive = 0;
                }
                else
                    m_inactive++;
            }

            void draw( C_Sprite& sprite)
            {
                size_t vertex_count = m_count * 4;

                if(vertex_count + 4 > m_vertices.size())
                    m_vertices.resize(m_vertices.size() + 4);

                sf::Vector2f position(sprite.m_subtexture.m_rect.left, sprite.m_subtexture.m_rect.top);
                sf::Vector2f size(sprite.m_subtexture.m_rect.width, sprite.m_subtexture.m_rect.height);

                sf::Transform transform = sprite.getSprite()->getTransform();

                m_vertices[vertex_count].position = transform.transformPoint(0.0f, 0.0f);
                m_vertices[vertex_count].texCoords = position;
               // m_vertices[vertex_count].color = sf::Color(0,0,0);

                m_vertices[vertex_count + 1].position = transform.transformPoint(0.0f, size.y);
                m_vertices[vertex_count + 1].texCoords = sf::Vector2f(position.x, size.y + position.y);
               // m_vertices[vertex_count + 1].color = sf::Color(0,0,0);

                m_vertices[vertex_count + 2].position = transform.transformPoint(size);
                m_vertices[vertex_count + 2].texCoords = size + position;
               // m_vertices[vertex_count + 2].color = sf::Color(0,0,0);

                m_vertices[vertex_count + 3].position = transform.transformPoint(size.x, 0.0f);
                m_vertices[vertex_count + 3].texCoords = sf::Vector2f(size.x + position.x, position.y);
              //  m_vertices[vertex_count + 3].color = sf::Color(0,0,0);

                m_count++;
            }

            const sf::Texture* m_texture;
            int layer;
            unsigned int m_inactive;
            unsigned int m_count;
            //unsigned int m_reserved;
            std::vector<sf::Vertex> m_vertices;
        };

        Batch* findBatch(const C_Sprite& sprite);
        void draw(sf::RenderTarget& target, sf::RenderStates state) const;

        std::vector<Batch*> m_batches;
    };




}



#endif