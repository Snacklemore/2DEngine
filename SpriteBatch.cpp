//
// Created by root on 13.05.20.
//

#include "SpriteBatch.h"
namespace moony {
    void SpriteBatch::clear()
    {
        for(unsigned int i = 0; i < m_batches.size(); i++)
        {
            m_batches[i]->clear();

            if(m_batches[i]->m_inactive > 256)
            {
                std::swap(m_batches[i], m_batches.back());
                delete m_batches.back();
                m_batches.pop_back();
                i--;
            }
        }
    }



    SpriteBatch::Batch* SpriteBatch::findBatch(const C_Sprite& sprite)
    {
        for(Batch* batch : m_batches)
        {
            if(batch->m_texture == sprite.m_subtexture.m_texture && batch->layer == sprite.GetSortOrder())
                return batch;
        }

        Batch* batch = new Batch();
        batch->m_texture = sprite.m_subtexture.m_texture;
        batch->layer = sprite.GetSortOrder();
        batch->m_inactive = 0;
        batch->m_count = 0;

        m_batches.push_back(batch);
        return m_batches.back();
    }



    void SpriteBatch::draw(C_Sprite& sprite)
    {
        if(sprite.m_subtexture.m_texture == NULL)
            return;

        findBatch(sprite)->draw(sprite);
    }



    void SpriteBatch::order()
    {
        // Sort the batches
        std::sort(m_batches.begin(), m_batches.end(), [&](const Batch* a_batch, const Batch* b_batch)
        {
            //if(a_batch->layer == b_batch->layer)
                //return a_batch->m_texture < b_batch->m_texture;

            return a_batch->layer < b_batch->layer;
        });
    }



    void SpriteBatch::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        int drawCalls = 0;
        for(const Batch* batch : m_batches)
        {

            states.texture = batch->m_texture;
            target.draw(batch->m_vertices.data(), batch->m_count * 4, sf::PrimitiveType::Quads, states);
            drawCalls++;

        }
    }
}