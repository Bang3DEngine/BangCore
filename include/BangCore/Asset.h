#pragma once

#include <functional>
#include <vector>

#include "BangCore/Array.h"
#include "BangCore/Array.tcc"
#include "BangCore/EventEmitter.h"
#include "BangCore/EventListener.tcc"
#include "BangCore/Map.h"
#include "BangCore/MetaNode.h"
#include "BangCore/Path.h"
#include "BangCore/Serializable.h"
#include "BangCore/String.h"

namespace Bang
{
class IEventsAsset;

class Asset : public Serializable,
              public EventEmitter<IEventsDestroy>,
              public EventEmitter<IEventsAsset>
{
public:
    void RemoveEmbeddedAsset(Asset *asset);
    void RemoveEmbeddedAsset(const String &embeddedAssetName);
    void PropagateAssetChanged();

    void ReImport();
    Path GetAssetFilepath() const;
    Asset *GetParentAsset() const;
    const Array<AH<Asset>> &GetEmbeddedAssets() const;
    Asset *GetEmbeddedAsset(const GUID &embeddedResGUID) const;
    Asset *GetEmbeddedAsset(const String &embeddedAssetName) const;
    Asset *GetEmbeddedAsset(GUID::GUIDType embeddedResGUID) const;
    String GetEmbeddedAssetName(GUID::GUIDType embeddedResGUID) const;

protected:
    Asset();
    virtual ~Asset() override;

    void ClearEmbeddedAssets();

    // Serializable
    virtual void ImportMeta(const MetaNode &metaNode) override;
    virtual void ExportMeta(MetaNode *metaNode) const override;

    // Asset
    virtual void Import(const Path &assetFilepath);
    void Import_(const Path &assetFilepath);

private:
    // Embedded asset related variables
    AH<Asset> p_parentAsset;
    Array<AH<Asset>> m_embeddedAssets;
    Map<String, Asset *> m_nameToEmbeddedAsset;
    Map<Asset *, String> m_embeddedAssetToName;
    Map<GUID, Asset *> m_GUIDToEmbeddedAsset;
    mutable GUID::GUIDType m_nextNewEmbeddedAssetGUID = 1;

    void AddEmbeddedAsset(const String &embeddedAssetName,
                          Asset *embeddedAsset);
    GUID::GUIDType GetNewEmbeddedAssetGUID() const;

    void SetParentAsset(Asset *parentAsset);

    friend class Assets;
};

#define ASSET_ABSTRACT(CLASSNAME)    \
    SERIALIZABLE_ABSTRACT(CLASSNAME) \
    friend class Assets;

#define ASSET(CLASSNAME)    \
    SERIALIZABLE(CLASSNAME) \
    friend class Assets;
}

