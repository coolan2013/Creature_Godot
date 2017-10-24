#pragma once
#include <vector>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <string>
#include "glm.hpp"

class meshRenderBoneComposition;

namespace CreatureModule
{
    class CreatureMetaData
    {
    public:
        CreatureMetaData(const std::string& json_str);
        virtual ~CreatureMetaData();

        bool getIsValid() const { return is_valid; }

        bool buildSkinSwapIndices(
            const std::string& swap_name,
            meshRenderBoneComposition * bone_composition,
            std::function<void(int, int)> indices_callback,
            int& total_size
        );

        void updateIndicesAndPoints(
            glm::uint32 * src_indices,
            std::function<void(int, int)> dst_indices_callback,
            std::function<void(int, float, float)> dst_pts_callback,
            int num_indices,
            int num_pts,
            const std::string& anim_name,
            int time_in
        );

        bool addSkinSwap(const std::string& swap_name, const std::unordered_set<std::string>& set_in);

    protected:

        const std::vector<int> * sampleOrder(const std::string& anim_name, int time_in) const;

        std::unordered_map<int, std::pair<int, int>> mesh_map;
        std::unordered_map<std::string, std::unordered_map<int, std::vector<int>>> anim_order_map;
        std::unordered_map<std::string, std::unordered_map<int, std::string>> anim_events_map;
        std::unordered_map<std::string, std::unordered_set<std::string>> skin_swaps;
        bool is_valid;
    };
}