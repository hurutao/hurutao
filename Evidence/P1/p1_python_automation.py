import unreal

log_path = r"C:/Users/Administrator/Documents/ChatGPT/训练场/Evidence/P1/python_automation.log"
def write(msg):
    unreal.log("P1_PYTHON " + msg)
    with open(log_path, "a", encoding="utf-8") as f:
        f.write(msg + "\n")

write("ENGINE_VERSION=" + str(unreal.SystemLibrary.get_engine_version()))
package_path = "/Game/P1_Temp_Automation"
asset_name = "P1_Temp_DataAsset"
asset_path = package_path + "/" + asset_name
asset_tools = unreal.AssetToolsHelpers.get_asset_tools()
asset = asset_tools.create_asset(asset_name, package_path, unreal.DataAsset, unreal.DataAssetFactory())
if not asset:
    raise RuntimeError("CREATE_FAILED")
write("CREATED=" + asset.get_path_name())
unreal.EditorAssetLibrary.save_asset(asset_path, only_if_is_dirty=False)
write("SAVED=" + str(unreal.EditorAssetLibrary.does_asset_exist(asset_path)))
loaded = unreal.EditorAssetLibrary.load_asset(asset_path)
write("READ=" + str(loaded is not None))
unreal.EditorAssetLibrary.delete_asset(asset_path)
write("DELETED=" + str(not unreal.EditorAssetLibrary.does_asset_exist(asset_path)))
unreal.SystemLibrary.quit_editor()
